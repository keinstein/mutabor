#
# Regular cron jobs for the mutabor package
#
0 4	* * *	root	[ -x /usr/bin/mutabor_maintenance ] && /usr/bin/mutabor_maintenance
