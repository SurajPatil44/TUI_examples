#include<ncurses.h>
#include<stdbool.h>
#include<unistd.h>

const char* errands[] = {"first do this","then do this","last do this"};


WINDOW *create_newwin(int ht,int wd,int stx,int sty,int* choice){
    WINDOW *local_win;

    local_win = newwin(ht,wd,stx,sty);
    box(local_win,0,0);
    move(sty+1,stx+1);
    switch(*choice){
        case(0):
            printw("first window.......");
            break;
        case(1):
            printw("second window.......");
            break;
        case(2):
            printw("third window.......");
            break;
        default:
            printw("WRONG.....");
            break;
    }
    wrefresh(local_win);
    return local_win;

}

void destroy_win(WINDOW *local_win){
    wborder(local_win,' ',' ',' ',' ',' ',' ',' ',' ');
    wrefresh(local_win);
    delwin(local_win);
}



void init(size_t num_choices){
    attroff(A_BOLD | A_UNDERLINE);
    for(int i=0;i < num_choices;i++){
        mvprintw(i,0,"%d.%s\n",i,errands[i]);
    }
    move(1,0);
}



void printscreen(int* cursor,char choice,size_t num_choices,bool* exit,WINDOW* my_win){
    attron(A_UNDERLINE | A_UNDERLINE);
    if(my_win) destroy_win(my_win);
    switch(choice){
        case('d'):
            //destroy_win(my_win);
            *cursor = (*cursor + 1) % num_choices;
            my_win = create_newwin(40,40,15,15,cursor);
            break;
        case('u'):
            //destroy_win(my_win);
            *cursor = (num_choices + *cursor - 1) % num_choices; 
            my_win = create_newwin(40,40,15,15,cursor);
            break;
        case('q'):
        default:
            //destroy_win(my_win);
            //clear();
            mvprintw(0,0,"pressed %d\n",(int) choice);
            mvprintw(1,1,"existing.........");
            *exit = true;
            break;
    }
    mvprintw(*cursor,0,"%d.%s\n",*cursor,errands[*cursor]);
    //return my_win;
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
    WINDOW* my_win = NULL;
    while(1){
        if(exit) break;
        //if(my_win) destroy_win(my_win);
        ch = getch();
        init(choices);
        printscreen(&cursor,(char) ch,choices,&exit,my_win);
        refresh();
    }
    getch();
    if(my_win) destroy_win(my_win);
    //sleep(50000);
    endwin();
    return 0;
}
