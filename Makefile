clevo_fanctrl_auto: clevo_fanctrl_auto.c
	@gcc clevo_fanctrl_auto.c -o clevo_fanctrl_auto
	@chmod +x clevo_fanctrl_auto

install:
	@cp clevo_fanctrl_auto /usr/bin/
	@cp clevo_fanctrl.service /lib/systemd/system/
	@systemctl daemon-reload
	@systemctl enable clevo_fanctrl.service
	@systemctl start clevo_fanctrl.service

uninstall:
	@systemctl stop clevo_fanctrl.service
	@systemctl disable clevo_fanctrl.service
	@systemctl daemon-reload
	@rm /usr/bin/clevo_fanctrl_auto
	@rm /lib/systemd/system/clevo_fanctrl.service
	@echo -e "VERY IMPORTANT !!!!! Press Fn+1 to restore original fan control"

clean:
	@rm clevo_fanctrl_auto
