################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Drawing.cpp \
../Polygon.cpp \
../PolygonMain.cpp 

CPP_DEPS += \
./Drawing.d \
./Polygon.d \
./PolygonMain.d 

OBJS += \
./Drawing.o \
./Polygon.o \
./PolygonMain.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/luap314/Documents/Unistuff/Programmieren 2 2026/Abgabe 3" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./Drawing.d ./Drawing.o ./Polygon.d ./Polygon.o ./PolygonMain.d ./PolygonMain.o

.PHONY: clean--2e-

