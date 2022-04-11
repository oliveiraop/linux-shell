# linux-shell
Operating Systems lab on 2022.1


## Programa para simular shell no linux

Com objetivo de aprender a utilizar as chamadas de sistemas, fizemos uma aplicação que se comporta como um shell no sistema linux.

## Como rodar

~~~
make all
./myshell
~~~

## Comandos do shell

~~~
start [command] [options] // run command in background mode
run [command] [options] // run command and wait for it to finish
wait // get signals sent by programs started with start command
kill [pid] // kill processes of the system (may require root privileges)
stop [pid] // Pause the execution of a process 
continue [pid] // Continue the execution of a process
~~~