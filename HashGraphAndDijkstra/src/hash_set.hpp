//Hao Dinh (804992)
//Paul Dao (881545)
//We certify that we worked cooperatively on this programming
//  assignment, according to the rules for pair programming


#ifndef HASH_SET_HPP_
#define HASH_SET_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <initializer_list>
#include "ics_exceptions.hpp"
#include "pair.hpp"
#include "iterator.hpp"
#include "set.hpp"


namespace ics {

template<class T> class HashSet : public Set<T>	{
  public:
    HashSet() = delete;
    HashSet(int (*ahash)(const T& element), double the_load_factor = 1.0);
    HashSet(int initial_bins, int (*ahash)(const T& element), double the_load_factor = 1.0);
    HashSet(const HashSet<T>& to_copy);
    HashSet(std::initializer_list<T> il, int (*ahash)(const T& element), double the_load_factor = 1.0);
    HashSet(ics::Iterator<T>& start, const ics::Iterator<T>& stop, int (*ahash)(const T& element), double the_load_factor = 1.0);
    virtual ~HashSet();

    virtual bool empty      () const;
    virtual int  size       () const;
    virtual bool contains   (const T& element) const;
    virtual std::string str () const;

    virtual bool contains (ics::Iterator<T>& start, const ics::Iterator<T>& stop) const;

    virtual int  insert (const T& element);
    virtual int  erase  (const T& element);
    virtual void clear  ();

    virtual int insert (ics::Iterator<T>& start, const ics::Iterator<T>& stop);
    virtual int erase  (ics::Iterator<T>& start, const ics::Iterator<T>& stop);
    virtual int retain (ics::Iterator<T>& start, const ics::Iterator<T>& stop);

    virtual HashSet<T>& operator = (const HashSet<T>& rhs);
    virtual bool operator == (const Set<T>& rhs) const;
    virtual bool operator != (const Set<T>& rhs) const;
    virtual bool operator <= (const Set<T>& rhs) const;
    virtual bool operator <  (const Set<T>& rhs) const;
    virtual bool operator >= (const Set<T>& rhs) const;
    virtual bool operator >  (const Set<T>& rhs) const;

    template<class T2>
    friend std::ostream& operator << (std::ostream& outs, const HashSet<T2>& s);

    virtual ics::Iterator<T>& ibegin () const;
    virtual ics::Iterator<T>& iend   () const;

  private:
    class LN;

  public:
    class Iterator : public ics::Iterator<T> {
      public:
        //KLUDGE should be callable only in begin/end
        Iterator(HashSet<T>* iterate_over, bool begin);
        Iterator(const Iterator& i);
        virtual ~Iterator();
        virtual T           erase();
        virtual std::string str  () const;
        virtual const ics::Iterator<T>& operator ++ ();
        virtual const ics::Iterator<T>& operator ++ (int);
        virtual bool operator == (const ics::Iterator<T>& rhs) const;
        virtual bool operator != (const ics::Iterator<T>& rhs) const;
        virtual T& operator *  () const;
        virtual T* operator -> () const;
      private:
        ics::pair<int,LN*> current; //Bin Index/Cursor; stop: LN* == nullptr
        HashSet<T>*        ref_set;
        int                expected_mod_count;
        bool               can_erase = true;
        void advance_cursors();
    };

    virtual Iterator begin () const;
    virtual Iterator end   () const;

  private:
    class LN {
      public:
        LN ()                      : next(nullptr){}
        LN (const LN& ln)          : value(ln.value), next(ln.next){}
        LN (T v,  LN* n = nullptr) : value(v), next(n){}

        T   value;
        LN* next;
    };

    LN** set      = nullptr;
    int (*hash)(const T& element);
    double load_factor;//used/bins <= load_factor
    int bins      = 1; //# bins available in the array
    int used      = 0; //# of key->value pairs in the hash table
    int mod_count = 0; //For sensing concurrent modification
    int   hash_compress (const T& element) const;
    void  ensure_load_factor(int new_used);
    LN*   find_element (int bin, const T& element) const;
    LN*   copy_list(LN*   l) const;
    LN**  copy_hash_table(LN** ht, int bins) const;
    void  delete_hash_table(LN**& ht, int bins);
  };





template<class T>
HashSet<T>::HashSet(int (*ahash)(const T& element), double the_load_factor)
    : hash(ahash), load_factor(the_load_factor) {
  //write code here
	set = new LN*[bins];
	set[used] = new LN();
}

template<class T>
HashSet<T>::HashSet(int initial_bins, int (*ahash)(const T& element), double the_load_factor)
    : bins(initial_bins), hash(ahash), load_factor(the_load_factor) {
  //write code here
	if (bins < 1)
		bins = 1;
	set = new LN*[bins];
	for (int i = 0; i < bins; i++)
	{
		set[i] = new LN();
	}
}

template<class T>
HashSet<T>::HashSet(const HashSet<T>& to_copy)
    : hash(to_copy.hash), load_factor(to_copy.load_factor), bins(to_copy.bins), used(to_copy.used) {
  //write code here
	set = copy_hash_table(to_copy.set, to_copy.bins);
}

template<class T>
HashSet<T>::HashSet(ics::Iterator<T>& start, const ics::Iterator<T>& stop, int (*ahash)(const T& element), double the_load_factor)
    : hash(ahash), load_factor(the_load_factor) {
  //write code here
	set = new LN*[bins];
	for (int i = 0; i < bins; i++)
		set[i] = new LN();
	insert(start, stop);
}

template<class T>
HashSet<T>::HashSet(std::initializer_list<T> il,int (*ahash)(const T& k), double the_load_factor)
    : hash(ahash), load_factor(the_load_factor) {
  //write code here
//	set = copy_hash_table(set, bins);
	set = new LN*[bins];
	for (int i = 0; i < bins; i++)
		set[i] = new LN();
	for (T element : il)
	{
		insert(element);
	}
}

template<class T>
HashSet<T>::~HashSet() {
  //write code here
	delete_hash_table(set, bins);
}


template<class T>
inline bool HashSet<T>::empty() const {
  //write code here
	return used == 0;
}

template<class T>
int HashSet<T>::size() const {
  //write code here
	return used;
}

template<class T>
bool HashSet<T>::contains (const T& element) const {
  //write code here
	return find_element(hash_compress(element), element) != nullptr;
}

template<class T>
std::string HashSet<T>::str() const {
  //write code here
	std::ostringstream outs;
	for (int i = 0; i < bins; i++)
	{
		LN* ln = set[i]; //new list node pointer
		outs << "bin[" << i << "]: ";
		for (; ln->next != nullptr; ln = ln->next)
		{
			outs << ln->value << " -> ";
		}
		outs << "#" << std::endl;
	}
	return outs.str();
}

template<class T>
bool HashSet<T>::contains(ics::Iterator<T>& start, const ics::Iterator<T>& stop) const {
  //write code here
	for (; start != stop; start++)
	{
		if (!contains(*start))
			return false;
	}
	return true;
}

template<class T>
int HashSet<T>::insert(const T& element) {
  //write code here
	++mod_count;
	LN* local = find_element(hash_compress(element), element);

	if (local != nullptr)
	{
		return 0;
	}

	ensure_load_factor(++used);

	set[hash_compress(element)] = new LN(element, set[hash_compress(element)]);

	return 1;

}

template<class T>
int HashSet<T>::erase(const T& element) {
  //write code here
	LN* ln = find_element(hash_compress(element), element);
		if (ln == nullptr)
			return 0;
		else
		{
			LN* to_delete = ln->next;
			ln->value = to_delete->value;
			ln->next = to_delete->next;
			delete to_delete;
			to_delete = nullptr;
			--used;
			++mod_count;
			return 1;
		}
}

template<class T>
void HashSet<T>::clear() {
  //write code here
	for (int i = 0; i < bins; i++)
	{
		for (LN* ln = set[i]; ln->next != nullptr; ln = set[i])
		{
			set[i] = ln->next;
			delete ln;
		}
	}
	used = 0;
	mod_count++;

}

template<class T>
int HashSet<T>::insert(ics::Iterator<T>& start, const ics::Iterator<T>& stop) {
  //write code here
	int count = 0;
	for (; start != stop; start++)
	{
			++count;
		insert(*start);
	}
	return count;

}

template<class T>
int HashSet<T>::erase(ics::Iterator<T>& start, const ics::Iterator<T>& stop) {
  //write code here
	int count = 0;
	for (; start != stop; start++)
	{
		++count;
		erase(*start);
	}
	return count;
}

template<class T>
int HashSet<T>::retain(ics::Iterator<T>& start, const ics::Iterator<T>& stop) {
  //write code here
	HashSet<T> s(start, stop, hash, load_factor);
	int count = 0;
	for (int i = 0; i < bins; i++)
	{
		for (LN* ln = set[i]; ln->next != nullptr;)
		{
			if (!s.contains(ln->value))
			{
				erase(ln->value);
			}
			else
			{
				++count;
				ln = ln->next;
			}
		}
	}
	return count;
}

template<class T>
HashSet<T>& HashSet<T>::operator = (const HashSet<T>& rhs) {
  //write code here
	if (this == &rhs)
		return *this;
	delete_hash_table(set, bins);
	used = rhs.size();
	bins = rhs.bins;
	load_factor = rhs.load_factor;
	hash = rhs.hash;
	set = copy_hash_table(rhs.set, bins);
	return *this;
}

template<class T>
bool HashSet<T>::operator == (const Set<T>& rhs) const {
  //write code here
	if (this == &rhs)
	{
		return true;
	}
	if (this->size() != rhs.size())
	{
	    return false;
	}
//	ics::Iterator<T>& rhs_i = rhs.ibegin();
	for (int i = 0; i < bins; i++)
	{
		for (LN* cursor = set[i]; cursor->next != nullptr; cursor = cursor->next)
		{

			if (!rhs.contains(cursor->value))
			{
				return false;
			}
		}
	}
	return true;
}

template<class T>
bool HashSet<T>::operator != (const Set<T>& rhs) const {
  //write code here
	  return !(*this == rhs);

}

template<class T>
bool HashSet<T>::operator <= (const Set<T>& rhs) const {
  //write code here
	if (this == &rhs)
		return false;
	if (used > rhs.size())
		return false;
	for (int i = 0; i < bins; i++)
	{
		for (LN* cursor = set[i]; cursor->next != nullptr; cursor = cursor->next)
		{
			if (!rhs.contains(cursor->value))
			{
				return false;
			}
		}
	}
	return true;
}

template<class T>
bool HashSet<T>::operator < (const Set<T>& rhs) const {
  //write code here
	 if (this == &rhs)
	    return false;
	 if (used >= rhs.size())
	    return false;
	 for (int i = 0; i < bins; i++)
	 {
	    for (LN* cursor = set[i]; cursor->next != nullptr; cursor = cursor->next)
		{
			if (!rhs.contains(cursor->value))
			{
				return false;
			}
		}
	  }

	  	return true;
}

template<class T>
bool HashSet<T>::operator >= (const Set<T>& rhs) const {
  //write code here
	  return rhs <= *this;

}

template<class T>
bool HashSet<T>::operator > (const Set<T>& rhs) const {
  //write code here
	  return rhs < *this;

}

template<class T>
std::ostream& operator << (std::ostream& outs, const HashSet<T>& s) {
  //write code here
	outs << "set[";
	if (!s.empty())
	{
		ics::Iterator<T>& setit = s.ibegin();
		outs << *setit;
		setit++;
		for (; setit != s.iend(); ++setit)
		{
			outs << "," << *setit;
		}
	}
	outs << "]";

	return outs;
}

//KLUDGE: memory-leak
template<class T>
auto HashSet<T>::ibegin () const -> ics::Iterator<T>& {
  return *(new Iterator(const_cast<HashSet<T>*>(this),true));
}

//KLUDGE: memory-leak
template<class T>
auto HashSet<T>::iend () const -> ics::Iterator<T>& {
  return *(new Iterator(const_cast<HashSet<T>*>(this),false));
}

template<class T>
auto HashSet<T>::begin () const -> HashSet<T>::Iterator {
  return Iterator(const_cast<HashSet<T>*>(this),true);
}

template<class T>
auto HashSet<T>::end () const -> HashSet<T>::Iterator {
  return Iterator(const_cast<HashSet<T>*>(this),false);
}

template<class T>
int HashSet<T>::hash_compress (const T& element) const {
  //write code here
	if (hash(element) < 0)
		return -(hash(element)) % bins;
	return hash(element) % bins;
}

template<class T>
void HashSet<T>::ensure_load_factor(int new_used) {
  //write code here
	if (load_factor >= double(new_used) / double(bins))
		return;

	LN** old_set = set;
	int old_bins = bins;

	bins *= 2;
	set = new LN*[bins];
	for (int i = 0; i < bins; i++)
		set[i] = new LN();

	for (int i = 0; i < old_bins; i++)
	{
		LN* ln = old_set[i];
		for (; ln->next != nullptr; ln = old_set[i])
		{
			int julian = hash_compress(ln->value);
			old_set[i] = ln->next;
			ln->next = set[julian];
			set[julian] = ln;
		}
		delete ln;
	}
	delete[] old_set;
}

template<class T>
typename HashSet<T>::LN* HashSet<T>::find_element (int bin, const T& element) const {
  for (LN* c = set[bin]; c->next!=nullptr; c=c->next)
    if (element == c->value)
      return c;

  return nullptr;
}

template<class T>
typename HashSet<T>::LN* HashSet<T>::copy_list (LN* l) const {
  if (l == nullptr)
    return nullptr;
  else
    return new LN(l->value, copy_list(l->next));
}

template<class T>
typename HashSet<T>::LN** HashSet<T>::copy_hash_table (LN** ht, int bins) const {
  //write code here
	LN** s = new LN*[bins];
	for (int i = 0; i < bins; i++)
	{
		s[i] = copy_list(ht[i]);
	}
	return s;
}

template<class T>
void HashSet<T>::delete_hash_table (LN**& ht, int bins) {
  //write code here
	for (int i = 0; i < bins; i++)
	{
		for (LN* ln = ht[i]; ln != nullptr; ln = set[i])
		{
			ht[i] = ln->next;
			delete ln;
		}
	}
	bins = 0;
	used = 0;
	delete[] ht;
	ht = nullptr;
}


template<class T>
void HashSet<T>::Iterator::advance_cursors(){
  //write code here
	if (current.first != -1)
		{
			current.second = current.second->next;
			if (current.second == nullptr || current.second->next == nullptr)
			{
				current.first++;
				while (current.first < ref_set->bins)
				{
					if (ref_set->set[current.first]->next != nullptr)
					{
						current.second = ref_set->set[current.first];
						break;
					}
					current.first++;
				}
				if (current.first == ref_set->bins)
				{
					current.first = -1;
					current.second = nullptr;
				}
			}
		}
}




template<class T>
HashSet<T>::Iterator::Iterator(HashSet<T>* iterate_over, bool begin) : ref_set(iterate_over) {
  //write code here
	if (begin)
	{
		if (ref_set->used == 0)
			current = ics::pair<int, LN*>(-1, nullptr);
		else
		{
			current.first = 0;
			current.second = ref_set->set[0];
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
	expected_mod_count = ref_set->mod_count;
}


template<class T>
HashSet<T>::Iterator::Iterator(const Iterator& i) :
    current(i.current), ref_set(i.ref_set), expected_mod_count(i.expected_mod_count), can_erase(i.can_erase) {}

template<class T>
HashSet<T>::Iterator::~Iterator() {}

template<class T>
T HashSet<T>::Iterator::erase() {
  if (expected_mod_count != ref_set->mod_count)
    throw ConcurrentModificationError("HashSet::Iterator::erase");
  if (!can_erase)
    throw CannotEraseError("HashSet::Iterator::erase Iterator cursor already erased");
  if (current.second == nullptr)
    throw CannotEraseError("HashSet::Iterator::erase Iterator cursor beyond data structure");

  //write code here
	can_erase = false;
	T to_return = current.second->value;
	ref_set->erase(to_return); ////?
	if (current.second->next == nullptr)
		advance_cursors();
	expected_mod_count = ref_set->mod_count;
	return to_return;
}

template<class T>
std::string HashSet<T>::Iterator::str() const {
  //write code here
	 std::ostringstream answer;
	  answer << ref_set->str() << "(current=" << current.first << "/" << current.second << ",expected_mod_count=" << expected_mod_count << ",can_erase=" << can_erase << ")";
	  return answer.str();
}

template<class T>
const ics::Iterator<T>& HashSet<T>::Iterator::operator ++ () {
  if (expected_mod_count != ref_set->mod_count)
    throw ConcurrentModificationError("HashSet::Iterator::operator ++");

  //write code here
  if (current.second == nullptr )
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
template<class T>
const ics::Iterator<T>& HashSet<T>::Iterator::operator ++ (int) {
  if (expected_mod_count != ref_set->mod_count)
    throw ConcurrentModificationError("HashSet::Iterator::operator ++(int)");

  //write code here
  if (current.second == nullptr)
    {
  	  return *this;
    }
  //
    Iterator* to_return = new Iterator(ref_set, true);
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

template<class T>
bool HashSet<T>::Iterator::operator == (const ics::Iterator<T>& rhs) const {
  const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
  if (rhsASI == 0)
    throw IteratorTypeError("HashSet::Iterator::operator ==");
  if (expected_mod_count != ref_set->mod_count)
    throw ConcurrentModificationError("HashSet::Iterator::operator ==");
  if (ref_set != rhsASI->ref_set)
    throw ComparingDifferentIteratorsError("HashSet::Iterator::operator ==");

  //write code here
  return current == rhsASI->current;

}


template<class T>
bool HashSet<T>::Iterator::operator != (const ics::Iterator<T>& rhs) const {
  const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
  if (rhsASI == 0)
    throw IteratorTypeError("HashSet::Iterator::operator !=");
  if (expected_mod_count != ref_set->mod_count)
    throw ConcurrentModificationError("HashSet::Iterator::operator !=");
  if (ref_set != rhsASI->ref_set)
    throw ComparingDifferentIteratorsError("HashSet::Iterator::operator !=");

  //write code here
  return (!(*this == rhs));

}

template<class T>
T& HashSet<T>::Iterator::operator *() const {
  if (expected_mod_count !=
      ref_set->mod_count)
    throw ConcurrentModificationError("HashSet::Iterator::operator *");
  if (!can_erase || current.second == nullptr)
    throw IteratorPositionIllegal("HashSet::Iterator::operator * Iterator illegal: exhausted");

  //write code here
  return current.second->value;

}

template<class T>
T* HashSet<T>::Iterator::operator ->() const {
  if (expected_mod_count !=
      ref_set->mod_count)
    throw ConcurrentModificationError("HashSet::Iterator::operator *");
  if (!can_erase || current.second == nullptr)
    throw IteratorPositionIllegal("HashSet::Iterator::operator * Iterator illegal: exhausted");

  //write code here
  return &(current.second->value);

}

}

#endif /* HASH_SET_HPP_ */
