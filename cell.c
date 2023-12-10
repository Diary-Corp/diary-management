//
// Created by march on 10/24/2023.
//

#include "cell.h"
#include <stdlib.h>

t_d_cell* createCell(int value, int nb_levels){
    /*
     * Create a cell using parameters information.
     */
    t_d_cell *myCell = (t_d_cell *) malloc(sizeof (t_d_cell));

    myCell->value = value;
    myCell->nb_levels = nb_levels;
    myCell->next = (t_d_cell**) malloc(sizeof (t_d_cell*)* nb_levels);

    for (int i=0; i < nb_levels; i++){
        myCell->next[i] = NULL;
    }

    return myCell;
}
