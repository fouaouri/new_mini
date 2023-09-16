# Minishell Todo List
- [x] Close fds, and handle signals

## Parsing Cases
- [ ] Handle Syntax error. Its not working :
```bash
|ls 
```
```bash
echo >
```
shouldn't work
- [ ] Expand from env from
```c
g_data.l_env
```
=> global variable
- [ ] Handle expand in heredoc

## Builtins
- [x] unset
- [x] export
- [x] env
- [x] exit
- [x] CD
- [x] pwd
- [x] echo

## HANDLE error on Builtins Over pipes
