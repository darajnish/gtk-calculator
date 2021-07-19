
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "stack.h"
#include "stringbuffer.h"

void on_activate(GtkApplication *app, gpointer user_data);
void on_ent_activate(GtkWidget *ent, gpointer data);
double solve_expression(const char *expr);

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("sng.example.calku", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);
    printf("status = %d\n", status);
    return status;
}

void on_activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *win;
    GtkWidget *box;
    GtkWidget *lb;
    GtkWidget *ent;

    win = gtk_application_window_new(app);

    gtk_window_set_title( GTK_WINDOW(win), "Calkuc");
    gtk_window_set_resizable( GTK_WINDOW(win), gtk_false());

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_size_request(GTK_WIDGET(box), 500, 75);
    gtk_container_add( GTK_CONTAINER(win), box);

    lb = gtk_label_new("= ");
    gtk_widget_set_size_request(GTK_WIDGET(lb), 500, 50);
    gtk_label_set_xalign(GTK_LABEL(lb), 0.0);
    gtk_widget_set_margin_start(GTK_WIDGET(lb), 10);
    gtk_container_add(GTK_CONTAINER(box), lb);

    ent = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(ent), "Evaluate..");
    gtk_container_add(GTK_CONTAINER(box), ent);
    g_signal_connect(ent, "activate", G_CALLBACK(on_ent_activate), lb);

    gtk_widget_show_all(win);
}

void on_ent_activate(GtkWidget *ent, gpointer data) {
    const gchar *buftext;
    char *text;
    GtkWidget *lb;
    lb = (GtkWidget*) data;
    
    buftext = gtk_entry_get_text(GTK_ENTRY(ent));
    text = (char*) malloc(sizeof(char)*10);
    sprintf(text, "= %.6G", solve_expression(buftext));
    gtk_label_set_text(GTK_LABEL(lb), text);
    gtk_entry_set_text(GTK_ENTRY(ent), "");

    free(text);
}

int prec(char a) {
    switch (a) {
        case '/':
        case '*': return 2;
        case '+':
        case '-': return 1;
        default: return -1;
    }
}

ExpStack* parse_expression(const char *expr) {
    StringBuffer *buff;
    CharStack *opts;
    ExpStack *stack;
    int n, i;
    char c;
    double op;

    if (expr == NULL) {
        return NULL;
    }

    n = strlen(expr);
    buff = strbuf_new();
    opts = stack_char_new();
    stack = stack_exp_new();
    
    for (i=0; i<n; i++) {
        c = expr[i];
        
        if (((c >= '0' && c <= '9') || c == '.') || ((c == '+' || c == '-') && (i == 0 || expr[i-1] == '('))) {
            strbuf_append_char(buff, c);
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (expr[i-1] != ')') {
                int e;
                e = strbuf_parse_number(buff, &op);

                if (buff->len == 0 || e != 0) {
                    printf("Error:: Unable to parse: %s\n", buff->str);
                    return NULL;
                }

                strbuf_empty(buff);
                stack_exp_push_num(stack, op);
            }
            
            while (opts->len > 0 && prec(stack_char_peek(opts)) >= prec(c)) {
                stack_exp_push_opt(stack, stack_char_pop(opts));
            }
            stack_char_push(opts, c);
        } else if (c == '(') {
            stack_char_push(opts, c);
        } else if ( c == ')' ) {
            strbuf_parse_number(buff, &op);
            strbuf_empty(buff);
            stack_exp_push_num(stack, op);

            while (opts->len > 0 && stack_char_peek(opts) != '(') {
                stack_exp_push_opt(stack, stack_char_pop(opts));
            }

            if (opts->len > 0 && stack_char_peek(opts) != '(') {
                printf("Error:: Invalid Expression: %s\n", expr);
                return NULL;
            }

            stack_char_pop(opts);
        }
    }

    if (buff->len > 0) {
        strbuf_parse_number(buff, &op);
        strbuf_empty(buff);
        stack_exp_push_num(stack, op);
    }
    while (opts->len != 0) {
        stack_exp_push_opt(stack, stack_char_pop(opts));
    }

    strbuf_free(buff);
    stack_char_free(opts);
    return stack;
}

double solve_expression(const char *expr) {
    ExpStack *expstack;
    NumStack *opstack;
    double res;

    opstack = stack_num_new();
    res = 0.0;

    expstack = parse_expression(expr);
    if (expstack == NULL)
        return 0.0;

    for (int i=0; i<expstack->len; i++) {
        ExpStackCell cell = expstack->data[i];
        
        if (cell.type == EXP_NUMBER) {
            stack_num_push(opstack, cell.value.num);
        } else if (cell.type == EXP_OPERATOR) {
            double op1, op2;

            op2 = stack_num_pop(opstack);
            op1 = stack_num_pop(opstack);

            switch (cell.value.opt) {
                case '/': stack_num_push(opstack, (op1 / op2));
                    break;
                case '*': stack_num_push(opstack, (op1 * op2));
                    break;
                case '+': stack_num_push(opstack, (op1 + op2));
                    break;
                case '-': stack_num_push(opstack, (op1 - op2));
                    break;
            }
        }
    }

    res = stack_num_pop(opstack);

    stack_exp_free(expstack);
    stack_num_free(opstack);
    return res;
}
