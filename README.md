# Minishell Todo List
- [x] Close fds, and handle signals

## Parsing Cases
- [ ] Handle Syntax error. Its not working : ```bash |ls ``` shouldn't work,also ... ```bash echo >```
- [ ] Expand from env from ```c g_data.l_env ``` => global variable
- [ ] Handle expand in heredoc

## Builtins
- [x] unset
- [x] export
- [x] env
- [ ] CD
- [ ] pwd
- [ ] echo
