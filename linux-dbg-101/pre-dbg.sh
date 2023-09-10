#!/usr/bin/env bash

sed -i 's,^GRUB_HIDDEN_TIMEOUT=0,GRUB_HIDDEN_TIMEOUT=,' /etc/default/grub
sed -i 's,^GRUB_HIDDEN_TIMEOUT_QUIET=true,GRUB_HIDDEN_TIMEOUT_QUIET=false,' /etc/default/grub
sed -i 's,^GRUB_TIMEOUT=10,GRUB_TIMEOUT=3,' /etc/default/grub

grep -m 1 -A 10 -E "Ubuntu, with Linux $(uname -r)" /boot/grub/grub.cfg | sed 's/quiet splash/no_suspend_console debug loglevel=9 kgdboc=ttyS0,115200 kgdbwait single/' | sed 's/Ubuntu, with Linux '"$(uname -r)"'/GNU\/Linux Ubuntu | kgdb ['"$(uname -r)"']/'
#grep -m 1 -A 10 -E "Ubuntu, with Linux $(uname -r)" /boot/grub/grub.cfg | sed 's/quiet splash/no_suspend_console debug loglevel=9 kgdboc=ttyS0,115200 kgdbwait single/' | sed 's/Ubuntu, with Linux $(uname -r)/GNU\/Linux Ubuntu | kgdb [$(uname -r)]/' | tee -a /etc/grub.d/40_custom

update-grub

apt-get install linux-source linux-tools-common \
linux-tools-$(uname -r | awk -F - '{print $1 "-" $2}') \
linux-image-$(uname -r)-dbgsym \
libc-bin-dbgsym \
libc-dev-bin-dbgsym \
libc6-dbgsym \
 \
cgdb git openssh-server

# systemtap, ktap, lttng, trace-cmd, dtrace

#for file in `find /usr/lib/debug -name '*.ko' -print`
#do
#	buildid=`eu-readelf -n $file| grep Build.ID: | awk '{print $3}'`
#	dir=`echo $buildid | cut -c1-2`
#	fn=`echo $buildid | cut -c3-`
#	mkdir -p /usr/lib/debug/.build-id/$dir
#	ln -s $file /usr/lib/debug/.build-id/$dir/$fn
#	ln -s $file /usr/lib/debug/.build-id/$dir/${fn}.debug
#done

