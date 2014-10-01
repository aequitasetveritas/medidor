################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/Programas/Code Composer Studio 6/ccsv6/tools/compiler/msp430_4.3.1

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./esp430ce1a.obj" \
"./fll.obj" \
"./interrupciones.obj" \
"./lcd_16x2.obj" \
"./main.obj" \
"./medidor.obj" \
"../lnk_msp430fe427a.cmd" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
MedidorV2_FE427A.out \

EXE_OUTPUTS__QUOTED += \
"MedidorV2_FE427A.out" \

BIN_OUTPUTS += \
MedidorV2_FE427A.txt \

BIN_OUTPUTS__QUOTED += \
"MedidorV2_FE427A.txt" \


# All Target
all: MedidorV2_FE427A.out secondary-outputs

# Tool invocations
MedidorV2_FE427A.out: $(OBJS) $(CMD_SRCS) $(A_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"D:/Programas/Code Composer Studio 6/ccsv6/tools/compiler/msp430_4.3.1/bin/cl430" -vmsp --abi=eabi -O4 --advice:power=all -g --define=__MSP430FE427A__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal -z -m"MedidorV2_FE427A.map" --heap_size=80 --stack_size=80 -i"D:/Programas/Code Composer Studio 6/ccsv6/ccs_base/msp430/include" -i"D:/Programas/Code Composer Studio 6/ccsv6/tools/compiler/msp430_4.3.1/lib" -i"D:/Programas/Code Composer Studio 6/ccsv6/tools/compiler/msp430_4.3.1/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="MedidorV2_FE427A_linkInfo.xml" --rom_model -o "MedidorV2_FE427A.out" $(ORDERED_OBJS) $(A_SRCS)
	@echo 'Finished building target: $@'
	@echo ' '

MedidorV2_FE427A.txt: $(EXE_OUTPUTS)
	@echo 'Invoking: MSP430 Hex Utility'
	"D:/Programas/Code Composer Studio 6/ccsv6/tools/compiler/msp430_4.3.1/bin/hex430" --ti_txt -o "MedidorV2_FE427A.txt" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "esp430ce1a.pp" "fll.pp" "interrupciones.pp" "lcd_16x2.pp" "main.pp" "medidor.pp" 
	-$(RM) "esp430ce1a.obj" "fll.obj" "interrupciones.obj" "lcd_16x2.obj" "main.obj" "medidor.obj" 
	-@echo 'Finished clean'
	-@echo ' '

secondary-outputs: $(BIN_OUTPUTS)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

