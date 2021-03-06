# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\User\Desktop\Hi\Demo1\TM_Mesh_System.cydsn\TM_Mesh_System.cyprj
# Date: Sat, 16 Jan 2021 19:08:25 GMT
#set_units -time ns
create_clock -name {UART_SCBCLK(FFB)} -period 1437.5 -waveform {0 718.75} [list [get_pins {ClockBlock/ff_div_1}]]
create_clock -name {CyRouted1} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyWCO} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/wco}]]
create_clock -name {CyLFClk} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyECO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/eco}]]
create_clock -name {CyIMO} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySysClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {UART_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 69 139} [list]
create_generated_clock -name {Clock_ReportTimer} -source [get_pins {ClockBlock/hfclk}] -edges {1 48001 96001} [list [get_pins {ClockBlock/udb_div_1}]]
create_generated_clock -name {OneWire_clock_delay} -source [get_pins {ClockBlock/hfclk}] -edges {1 48001 96001} [list [get_pins {ClockBlock/udb_div_3}]]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Users\User\Desktop\Hi\Demo1\TM_Mesh_System.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\User\Desktop\Hi\Demo1\TM_Mesh_System.cydsn\TM_Mesh_System.cyprj
# Date: Sat, 16 Jan 2021 19:08:17 GMT
