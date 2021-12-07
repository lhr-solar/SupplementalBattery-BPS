
gnome-terminal -- openocd -f /usr/share/openocd/scripts/interface/stlink-v2.cfg -f /usr/share/openocd/scripts/target/stm32f4x.cfg

gdb-multiarch ./Objects/bps-leader.elf -tui -ex "target extended-remote localhost:3333"

