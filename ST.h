# ifndef ST_H
# define ST_H

int data_offset = 0;
int data_location()
{
    data_offset -= 4;
    return data_offset;
}

struct symrec
{
  char *name;
  double val;
  int offset;
  enum {t_int, t_float, t_char } type;
  enum {t_variable, t_function, t_param} other;
  struct symrec *next;
};
typedef struct symrec symrec;
symrec *sym_table = (symrec *)0;
symrec * putsym ( char *sym_name, int type, double val, int otherType)
{
  symrec *ptr;
  ptr = (symrec *) malloc (sizeof(symrec));
  ptr->name = (char *) malloc (strlen(sym_name)+1);
  ptr->val = val;
  ptr->type = type;
  ptr->other = otherType;
  ptr->offset = data_location();
  strcpy (ptr->name,sym_name);
  ptr->next = (struct symrec *)sym_table;
  sym_table = ptr;
  return ptr;
}
symrec * getsym ( char *sym_name )
{
  symrec *ptr;
  for (ptr = sym_table; ptr != (symrec *) 0;
       ptr = (symrec *)ptr->next)
    if (strcmp (ptr->name,sym_name) == 0)
      return ptr;
  return 0;
}

#endif