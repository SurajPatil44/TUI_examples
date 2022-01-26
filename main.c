#include<ncurses.h>
#include<stdbool.h>


const char* errands[] = {"first do this","then do this","last do this"};

void init(size_t num_choices){
    attroff(A_BOLD | A_UNDERLINE);
    for(int i=0;i < num_choices;i++){
        mvprintw(i,0,"%d.%s\n",i,errands[i]);
    }
    move(1,0);
}

void printscreen(int* cursor,char choice,size_t num_choices,bool* exit){
    attron(A_UNDERLINE | A_UNDERLINE);
    switch(choice){
        case('d'):
            *cursor = (*cursor + 1) % num_choices;
            break;
        case('u'):
            *cursor = (num_choices + *cursor - 1) % num_choices; 
            break;
        case('q'):
        default:
            clear();
            mvprintw(0,0,"pressed %c\n",choice);
            mvprintw(1,1,"existing.........");
            *exit = true;
            break;
    }
    mvprintw(*cursor,0,"%d.%s\n",*cursor,errands[*cursor]);
}

int main(){
    int ch = 0;
    initscr();
    raw();
    keypad(stdscr,TRUE);
    noecho();
    bool exit = false;
    int cursor = 0,choices = 3;
    init(choices);
    while(1){
        if(exit) break;
        ch = getch();
        init(choices);
        printscreen(&cursor,(char) ch,choices,&exit);
        refresh();
    }
    //getch();
    endwin();
    return 0;
}
