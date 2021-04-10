singularity shell \
	    --bind /usr/opt/opt-buster:/usr/opt,/mnt/misc/sw/indep \
	    --bind /mnt/misc/sw/x86_64/all \
	    --bind /usr/lib/x86_64-linux-gnu/modulecmd.tcl \
	    /usr/opt/nscl-buster.img -c "bash -l"
