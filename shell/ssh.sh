#!/usr/bin/expect
spawn ssh root@192.168.1.124
expect "*password:"
send "rot\r"
expect "*#"
send "ls\r"
expect "*#"
send "cd /etc\r"
expect "*#"
send "exit\r"
interact
