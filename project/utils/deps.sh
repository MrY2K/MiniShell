42-wizzard-brew

sleep 0.5

brew install readline

sleep 0.2

brew install ncurses

sleep 0.2

brew link readline --force

sleep 0.2

export LDFLAGS="-L$(brew --prefix readline)/lib"
export CPPFLAGS="-I$(brew --prefix readline)/include"