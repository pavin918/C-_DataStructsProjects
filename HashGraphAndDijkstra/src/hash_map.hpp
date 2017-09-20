//Hao Dinh (804992)
//Paul Dao (881545)
//We certify that we worked cooperatively on this programming
//  assignment, according to the rules for pair programming

#ifndef HASH_MAP_HPP_
#define HASH_MAP_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <initializer_list>
#include "ics_exceptions.hpp"
#include "iterator.hpp"
#include "pair.hpp"
#include "map.hpp"
#include "array_queue.hpp"   //For traversal


namespace ics {

template<class KEY,class T> class HashMap : public Map<KEY,T>	{
  public:
    typedef ics::pair<KEY,T> Entry;
    HashMap() = delete;
    HashMap(int (*ahash)(const KEY& k), double the_load_factor = 1.0);
    HashMap(int initial_bins, int (*ahash)(const KEY& k), double the_load_factor = 1.0);
	  HashMap(const HashMap<KEY,T>& to_copy);
	  HashMap(std::initializer_list<Entry> il, int (*ahash)(const KEY& k), double the_load_factor = 1.0);
    HashMap(ics::Iterator<Entry>& start, const ics::Iterator<Entry>& stop, int (*ahash)(const KEY& k), double the_load_factor = 1.0);
	  virtual ~HashMap();

    virtual bool empty      () const;
    virtual int  size       () const;
    virtual bool has_key    (const KEY& key) const;
    virtual bool has_value  (const T& value) const;
    virtual std::string str () const;

    virtual T    put   (const KEY& key, const T& value);
    virtual T    erase (const KEY& key);
    virtual void clear ();

    virtual int put   (ics::Iterator<Entry>& start, const ics::Iterator<Entry>& stop);

    virtual T&       operator [] (const KEY&);
    virtual const T& operator [] (const KEY&) const;
    virtual HashMap<KEY,T>& operator = (const HashMap<KEY,T>& rhs);
    virtual bool operator == (const Map<KEY,T>& rhs) const;
    virtual bool operator != (const Map<KEY,T>& rhs) const;

    template<class KEY2,class T2>
    friend std::ostream& operator << (std::ostream& outs, const HashMap<KEY2,T2>& m);

    virtual ics::Iterator<Entry>& ibegin () const;
    virtual ics::Iterator<Entry>& iend   () const;

   private:
     class LN;

   public:
     class Iterator : public ics::Iterator<Entry> {
       public:
        //KLUDGE should be callable only in begin/end
        Iterator(HashMap<KEY,T>* iterate_over, bool begin);
        Iterator(const Iterator& i);
       virtual ~Iterator();
        virtual Entry       erase();
        virtual std::string str  () const;
        virtual const ics::Iterator<Entry>& operator ++ ();
        virtual const ics::Iterator<Entry>& operator ++ (int);
        virtual bool operator == (const ics::Iterator<Entry>& rhs) const;
        virtual bool operator != (const ics::Iterator<Entry>& rhs) const;
        virtual Entry& operator *  () const;
        virtual Entry* operator -> () const;
      private:
        ics::pair<int,LN*> current; //Bin Index/Cursor; stop: LN* == nullptr
        HashMap<KEY,T>*    ref_map;
        int                expected_mod_count;
        bool               can_erase = true;
        void advance_cursors();
    };

    virtual Iterator begin () const;
    virtual Iterator end   () const;
    //KLUDGE: define
    //virtual ics::Iterator<KEY>&  begin_key   () const;
    //virtual ics::Iterator<KEY>&  end_key     () const;
    //virtual ics::Iterator<T>&    begin_value () const;
    //virtual ics::Iterator<T>&    end_value   () const;

    private:
      class LN {
        public:
          LN ()                         : next(nullptr){}
          LN (const LN& ln)             : value(ln.value), next(ln.next){}
          LN (Entry v, LN* n = nullptr) : value(v), next(n){}

          Entry value;
          LN*   next;
      };

      LN** map      = nullptr;
      int (*hash)(const KEY& k);
      double load_factor;//used/bins <= load_factor
      int bins      = 1; //# bins available in the array
      int used      = 0; //# of key->value pairs in the hash table
      int mod_count = 0; //For sensing concurrent modification
      int   hash_compress (const KEY& key) const;
      void  ensure_load_factor(int new_used);
      LN*   find_key (int bin, const KEY& key) const;
      bool  find_value (const T& value) const;
      LN*   copy_list(LN*   l) const;
      LN**  copy_hash_table(LN** ht, int bins) const;
      void  delete_hash_table(LN**& ht, int bins);
  };





template<class KEY,class T>
HashMap<KEY,T>::HashMap(int (*ahash)(const KEY& k), double the_load_factor) : hash(ahash), load_factor(the_load_factor) {
  //write code here
	map = new LN*[bins];
	map[0] = new LN();


}

template<class KEY,class T>
HashMap<KEY,T>::HashMap(int initial_bins, int (*ahash)(const KEY& k), double the_load_factor) : bins(initial_bins), hash(ahash), load_factor(the_load_factor) {
  //write code here
	if (bins < 1)
		bins = 1;
	map = new LN*[bins];
	for (int i = 0; i < bins; i++)
	{
		map[i] = new LN();
	}
}

template<class KEY,class T>
HashMap<KEY,T>::HashMap(const HashMap<KEY,T>& to_copy) : hash(to_copy.hash), load_factor(to_copy.load_factor), bins(to_copy.bins), used(to_copy.used) {
  //write code here
	map = copy_hash_table(to_copy.map, bins);
}

template<class KEY,class T>
HashMap<KEY,T>::HashMap(ics::Iterator<Entry>& start, const ics::Iterator<Entry>& stop, int (*ahash)(const KEY& k), double the_load_factor) : hash(ahash), load_factor(the_load_factor) {
  //write code here
	map = new LN*[bins];
	for (int i = 0; i < bins; i++)
	{
		map[i] = new LN();
	}
	put(start, stop);
}

template<class KEY,class T>
HashMap<KEY,T>::HashMap(std::initializer_list<Entry> il,int (*ahash)(const KEY& k), double the_load_factor) : hash(ahash), load_factor(the_load_factor) {
  //write code here
	map = new LN*[bins];
	for (int i = 0; i < bins; i++)
	{
		map[i] = new LN();
	}
	for (Entry e : il)
	{
		put(e.first, e.second);
	}
}

template<class KEY,class T>
HashMap<KEY,T>::~HashMap() {
  //write code here
	delete_hash_table(map, bins);
}


template<class KEY,class T>
inline bool HashMap<KEY,T>::empty() const {
  //write code here
	return used == 0;
}

template<class KEY,class T>
int HashMap<KEY,T>::size() const {
  //write code here
	return used;
}

template<class KEY,class T>
bool HashMap<KEY,T>::has_key (const KEY& key) const {
  //write code here

	return find_key(hash_compress(key), key) != nullptr;

}

template<class KEY,class T>
bool HashMap<KEY,T>::has_value (const T& value) const {
  //write code here
	return find_value(value);
}

template<class KEY,class T>
std::string HashMap<KEY,T>::str() const {
  //write code here
	std::ostringstream outs;
	for (int i = 0; i < bins; i++)
	{
		LN* ln = map[i]; //new list node pointer
		outs << "bin[" << i << "]: ";
		for (; ln->next != nullptr; ln = ln->next)
		{
			outs << ln->value << " -> ";
		}
		outs << "#" << std::endl;
	}
	return outs.str();
}

template<class KEY,class T>
T HashMap<KEY,T>::put(const KEY& key, const T& value) {
  //write code here
	++mod_count;
	LN* local = find_key(hash_compress(key), key);

	if (local != nullptr)
	{
		T old_value = local->value.second;
		local->value.second = value;
		return old_value;
	}

	ensure_load_factor(++used);

	map[hash_compress(key)] = new LN(Entry(key, value), map[hash_compress(key)]);

	return map[hash_compress(key)]-> value.second;
}

template<class KEY,class T>
T HashMap<KEY,T>::erase(const KEY& key) {
  //write code here
	LN* ln = find_key(hash_compress(key), key);
	if (ln == nullptr)
		throw ics::KeyError("Key does not exist in map");
	else
	{
		LN* to_delete = ln->next;
		T return_value = ln->value.second;
		ln->value = to_delete->value;
		ln->next = to_delete->next;
		delete to_delete;
		to_delete = nullptr;
		--used;
		++mod_count;
		return return_value;
	}
}

template<class KEY,class T>
void HashMap<KEY,T>::clear() {
  //write code here
	for (int i = 0; i < bins; i++)
	{
		for (LN* point = map[i]; map[i]->next != nullptr; point = map[i])
		{
			map[i] = point->next;
			delete point;
		}
	}
	++mod_count;
	used = 0;
}

template<class KEY,class T>
int HashMap<KEY,T>::put (ics::Iterator<Entry>& start, const ics::Iterator<Entry>& stop) {
  //write code here
	int count = 0;
	for (; start != stop; start++)
	{
		++count;
		put(start->first, start->second);
	}
	return count;
}

template<class KEY,class T>
T& HashMap<KEY,T>::operator [] (const KEY& key) {
  //write code here
	if (has_key(key))
	{
		return find_key(hash_compress(key), key)->value.second;
	}
	else
	{
		ensure_load_factor(++used);
		map[hash_compress(key)] = new LN(Entry(key, T()), map[hash_compress(key)]);
		++mod_count;
		return map[hash_compress(key)]->value.second;
	}
}

template<class KEY,class T>
const T& HashMap<KEY,T>::operator [] (const KEY& key) const {
  //write code here
	if (has_key(key))
	{
		return find_key(hash_compress(key), key)->value.second;
	}

	std::ostringstream answer;
	throw KeyError(answer.str());
}

template<class KEY,class T>
bool HashMap<KEY,T>::operator == (const Map<KEY,T>& rhs) const {
  //write code here
	if (this == &rhs)
		return true;
	if (used != rhs.size())
		return false;

	for (int i = 0; i < bins; i++)
	{
		for (LN* cursor = map[i]; cursor->next != nullptr; cursor = cursor->next)
		{
			Entry e = cursor->value;

			if (rhs.has_key(e.first))
			{
				if (e.second != rhs[e.first])
					return false;
			}
			else
				return false;
		}
	}
	return true;
}

template<class KEY,class T>
HashMap<KEY,T>& HashMap<KEY,T>::operator = (const HashMap<KEY,T>& rhs) {
  //write code here
	if (this == &rhs)
		return *this;
	delete_hash_table(map, bins);
	used = rhs.size();
	bins = rhs.bins;
	load_factor = rhs.load_factor;
	hash = rhs.hash;
	map = copy_hash_table(rhs.map, bins);
	return *this;
}

template<class KEY,class T>
bool HashMap<KEY,T>::operator != (const Map<KEY,T>& rhs) const {
  //write code here
	return !(*this == rhs);
}


template<class KEY,class T>
std::ostream& operator << (std::ostream& outs, const HashMap<KEY,T>& m) {
  //write code here
	outs << "map[";
	if (!m.empty())
	{
		ics::Iterator<ics::pair<KEY, T>>& aqi = m.ibegin();
		outs << aqi->first << "->" << aqi->second;
		aqi++;
		for (; aqi != m.iend(); ++aqi)
		{
			outs << "," << aqi->first << "->" << aqi->second;
		}
	}
	outs << "]";

	return outs;
}

//KLUDGE: memory-leak
template<class KEY,class T>
auto HashMap<KEY,T>::ibegin () const -> ics::Iterator<Entry>& {
  return *(new Iterator(const_cast<HashMap<KEY,T>*>(this),true));
}

//KLUDGE: memory-leak
template<class KEY,class T>
auto HashMap<KEY,T>::iend () const -> ics::Iterator<Entry>& {
  return *(new Iterator(const_cast<HashMap<KEY,T>*>(this),false));
}

template<class KEY,class T>
auto HashMap<KEY,T>::begin () const -> HashMap<KEY,T>::Iterator {
  return Iterator(const_cast<HashMap<KEY,T>*>(this),true);
}

template<class KEY,class T>
auto HashMap<KEY,T>::end () const -> HashMap<KEY,T>::Iterator {
  return Iterator(const_cast<HashMap<KEY,T>*>(this),false);
}

template<class KEY,class T>
int HashMap<KEY,T>::hash_compress (const KEY& key) const {
  //write code here
	if (hash(key) < 0)
	{
		return (-(hash(key)) % bins);
	}

	return hash(key) % bins;
}

template<class KEY,class T>
void HashMap<KEY,T>::ensure_load_factor(int new_used) {
  //write code here
	if (double(new_used) / double(bins) <= load_factor)
		return;
	LN** old_map = map;
	int old_bins = bins;

	bins *= 2;
	map = new LN*[bins];

	for (int i = 0; i < bins; i++)
	{
		map[i] = new LN();
	}

	for (int i = 0; i < old_bins; i++)
	{
		LN* blah = old_map[i];
		for (; blah->next != nullptr; blah = old_map[i])
		{
			int corey = hash_compress(blah->value.first);
			old_map[i] = blah->next;
			blah->next = map[corey];
			map[corey] = blah;

		}

		delete blah;
	}

	delete[] old_map;
}

template<class KEY,class T>
typename HashMap<KEY,T>::LN* HashMap<KEY,T>::find_key (int bin, const KEY& key) const {
  //write code here
	if (hash_compress(key) != bin)
		return nullptr;
	for (LN* point = map[bin]; point->next != nullptr; point = point->next)
	{
		if (point->value.first == key)
		{
			return point;
		}
	}
	return nullptr;
}

template<class KEY,class T>
bool HashMap<KEY,T>::find_value (const T& value) const {
  //write code here
	for (int i = 0; i < bins; i++)
	{
		for (LN* point = map[i]; point->next != nullptr; point = point->next)
		{
			if (point->value.second == value)
			{
				return true;
			}
		}
	}
	return false;
}

template<class KEY,class T>
typename HashMap<KEY,T>::LN* HashMap<KEY,T>::copy_list (LN* l) const {
  //write code here
	LN* a = new LN(*l);
	LN* b = a;
	for (LN* ln = l->next; ln != nullptr; ln = ln->next)
	{
		b->next = new LN(*ln);
		b = b->next;
	}
	return a;
}

template<class KEY,class T>
typename HashMap<KEY,T>::LN** HashMap<KEY,T>::copy_hash_table (LN** ht, int bins) const {
  //write code here

	LN** m = new LN*[bins];
	for (int i = 0; i < bins; i++)
	{
		m[i] = copy_list(ht[i]);
	}
	return m;
}

template<class KEY,class T>
void HashMap<KEY,T>::delete_hash_table (LN**& ht, int bins) {
  //write code here
	for (int i = 0; i < bins; i++)
	{
		for (LN* point = ht[i]; point != nullptr; point = ht[i])
		{
			ht[i] = point->next;
			delete point;
		}
	}

	bins = 0;
	used = 0;
	delete[] ht;
	ht = nullptr;
}


template<class KEY,class T>
void HashMap<KEY,T>::Iterator::advance_cursors(){
  //write code here

	if (current.first != -1)
	{
		current.second = current.second->next;
		if (current.second == nullptr || current.second->next == nullptr)
		{
			current.first++;
			while (current.first < ref_map->bins)
			{
				if (ref_map->map[current.first]->next != nullptr)
				{
					current.second = ref_map->map[current.first];
					break;
				}
				current.first++;

			}
			if (current.first == ref_map->bins)
			{
				current.first = -1;
				current.second = nullptr;
			}
		}

	}
}

template<class KEY,class T>
HashMap<KEY,T>::Iterator::Iterator(HashMap<KEY,T>* iterate_over, bool begin) : ref_map(iterate_over) {
  //write code here

	if (begin)
	{
		if (ref_map->used == 0)
			current = ics::pair<int, LN*>(-1, nullptr);
		else
		{
			current.first = 0;
			current.second = ref_map->map[0];
			if (current.second->next == nullptr)
			{
				advance_cursors();

			}
		}
	}
	else
	{
		current = ics::pair<int, LN*>(-1, nullptr);
	}
	expected_mod_count = ref_map->mod_count;
}

template<class KEY,class T>
HashMap<KEY,T>::Iterator::Iterator(const Iterator& i) :
    current(i.current), ref_map(i.ref_map), expected_mod_count(i.expected_mod_count), can_erase(i.can_erase) {}

template<class KEY,class T>
HashMap<KEY,T>::Iterator::~Iterator()
{}

template<class KEY,class T>
auto HashMap<KEY,T>::Iterator::erase() -> Entry {
  if (expected_mod_count != ref_map->mod_count)
    throw ConcurrentModificationError("HashMap::Iterator::erase");
  if (!can_erase)
    throw CannotEraseError("HashMap::Iterator::erase Iterator cursor already erased");
  if (current.second == nullptr)
    throw CannotEraseError("HashMap::Iterator::erase Iterator cursor beyond data structure");


	can_erase = false;
	auto to_return = current.second->value;
//	advance_cursors();
	ref_map->erase(to_return.first); ////?
	if (current.second->next == nullptr)
		advance_cursors();
	expected_mod_count = ref_map->mod_count;
	return to_return;
	  //write code here
}

template<class KEY,class T>
std::string HashMap<KEY,T>::Iterator::str() const {
  std::ostringstream answer;
  answer << ref_map->str() << "(current=" << current.first << "/" << current.second << ",expected_mod_count=" << expected_mod_count << ",can_erase=" << can_erase << ")";
  return answer.str();
}

//KLUDGE: cannot use Entry
template<class KEY,class T>
auto  HashMap<KEY,T>::Iterator::operator ++ () -> const ics::Iterator<ics::pair<KEY,T>>& {
  if (expected_mod_count != ref_map->mod_count)
    throw ConcurrentModificationError("HashMap::Iterator::operator ++");

  //write code here

  if (current.second == nullptr )//current.first == ref_map->bins - 1 && current.second->next == nullptr)
  {
	  return *this;
  }

  if (!can_erase)
  {
	  can_erase = true;
  }
  else
  {
	  advance_cursors();
  }
  return *this;
}

//KLUDGE: creates garbage! (can return local value!)
template<class KEY,class T>
auto HashMap<KEY,T>::Iterator::operator ++ (int) -> const ics::Iterator<ics::pair<KEY,T>>&{
  if (expected_mod_count != ref_map->mod_count)
    throw ConcurrentModificationError("HashMap::Iterator::operator ++(int)");

  //write code here
  if (current.second == nullptr)
  {
	  return *this;
  }
  Iterator* to_return = new Iterator(ref_map, true);
  while (to_return->current.second != current.second)
  {
	  to_return->advance_cursors();
  }

  if (!can_erase)
  {
	 can_erase = true;
  }
  else
  {
 	 advance_cursors();
  }

   return *to_return;
}

template<class KEY,class T>
bool HashMap<KEY,T>::Iterator::operator == (const ics::Iterator<Entry>& rhs) const {
  const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
  if (rhsASI == 0)
    throw IteratorTypeError("HashMap::Iterator::operator ==");
  if (expected_mod_count != ref_map->mod_count)
    throw ConcurrentModificationError("HashMap::Iterator::operator ==");
  if (ref_map != rhsASI->ref_map)
    throw ComparingDifferentIteratorsError("HashMap::Iterator::operator ==");
  //write code here

  return current == rhsASI->current;
}


template<class KEY,class T>
bool HashMap<KEY,T>::Iterator::operator != (const ics::Iterator<Entry>& rhs) const {
  const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
  if (rhsASI == 0)
    throw IteratorTypeError("HashMap::Iterator::operator !=");
  if (expected_mod_count != ref_map->mod_count)
    throw ConcurrentModificationError("HashMap::Iterator::operator !=");
  if (ref_map != rhsASI->ref_map)
    throw ComparingDifferentIteratorsError("HashMap::Iterator::operator !=");

  //write code here
  return (!(*this == rhs));
}

template<class KEY,class T>
ics::pair<KEY,T>& HashMap<KEY,T>::Iterator::operator *() const {
  if (expected_mod_count !=
      ref_map->mod_count)
  {
    throw ConcurrentModificationError("HashMap::Iterator::operator *");
  }
  if (!can_erase || current.second == nullptr)
  {
	  throw IteratorPositionIllegal("HashMap::Iterator::operator * Iterator illegal: exhausted");
  }
  return current.second->value;
  //write code here
}

template<class KEY,class T>
ics::pair<KEY,T>* HashMap<KEY,T>::Iterator::operator ->() const {
  if (expected_mod_count !=
      ref_map->mod_count){
    throw ConcurrentModificationError("HashMap::Iterator::operator *");
  }
  if (!can_erase || current.second == nullptr)
  {
    throw IteratorPositionIllegal("HashMap::Iterator::operator -> Iterator illegal: exhausted");
  }
  //write code here
  return &(current.second->value);
}

}

#endif /* HASH_MAP_HPP_ */
