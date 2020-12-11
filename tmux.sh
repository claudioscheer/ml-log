#!/bin/sh

session="ml-log"
# tmux kill-session -t $session
session_exists=$(tmux list-sessions | grep $session)

if [ "$session_exists" = "" ]; then
    tmux new-session -d -s $session -x "$(tput cols)" -y "$(tput lines)"

    tmux rename-window -t 0 "vim"
    tmux send-keys -t 0 "vim -c 'Lex'" C-m
    tmux split-window -v -p 25
    tmux select-pane -t 0
fi

tmux select-window -t $session:0
tmux attach-session -t $session
