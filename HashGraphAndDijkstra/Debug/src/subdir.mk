################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/dijkstra.cpp \
../src/driver_graph.cpp \
../src/test_graph.cpp 

OBJS += \
./src/dijkstra.o \
./src/driver_graph.o \
./src/test_graph.o 

CPP_DEPS += \
./src/dijkstra.d \
./src/driver_graph.d \
./src/test_graph.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"C:\Users\Kirito\workspace\courselib\src" -I"C:\Users\Kirito\workspace\googletestlib\include" -O0 -g3 -Wall -c -fmessage-length=0 -std=gnu++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


