//
//  stack.h
//  RPNcalculator
//
//  Created by Abdi Asfaw on 3/31/15.
//  Copyright (c) 2015 Abdi Asfaw. All rights reserved.
//

#ifndef RPNcalculator_stack_h
#define RPNcalculator_stack_h

#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

template <class value>
struct node {
    value data;
    node *next;
};


template <class value>
struct stack{
    
    node<value> *top;
    
    stack()
    {
        top=0;
    }
    void push(value element)
    {
        node<value> *temp=new node<value>;
        if (temp!=0)
        {
            temp->data=element;
            temp->next=top;
            top=temp;
        }
    }
    
    value pop()
    {
        node<value> *tmp;
        value item=0;
        if(!empty())
        {
            tmp=top;
            item=tmp->data;
            top=tmp->next;
            delete tmp;
        }
        return item;
    }
    
    value peep()
    {
        return  top->data;
    }
    bool empty()
    {
        return top==0;
    }
};


#endif
