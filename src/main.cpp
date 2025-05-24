#include <iostream>
#include <manager.h>


int main(){
    Manager manager;

    while (manager.running()){
        manager.update();
        manager.render();
    }
}