################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/TemplateRecursive.cpp \
../src/TemplateRecursiveMain.cpp 

CPP_DEPS += \
./src/TemplateRecursive.d \
./src/TemplateRecursiveMain.d 

OBJS += \
./src/TemplateRecursive.o \
./src/TemplateRecursiveMain.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/TemplateRecursive.d ./src/TemplateRecursive.o ./src/TemplateRecursiveMain.d ./src/TemplateRecursiveMain.o

.PHONY: clean-src

