#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct node
{
    char info[201];
    struct node *left;
    struct node *right;
}tree_type;

void insert(tree_type **rt,char str[201])
{
     tree_type *p;
     p=(tree_type*)malloc(sizeof(tree_type));
     if(p!=NULL)
     {
          strcpy(p->info,str);
          p->right=NULL;
          p->left=NULL;
          if(*rt==NULL)
               *rt=p;
          else
          {
                if(strcmp(str,((*rt)->info))<0)
                  insert(&((*rt)->left),str);
                else
                  insert(&((*rt)->right),str);
          }
     }
}
void display(tree_type *rt)
{
    if(rt==NULL)
    {
        return;
    }
    else
    {
        display(rt->left);
        if (strcmp(rt->info,"\0") != 0)
		    printf("%s\n",rt->info);
        display(rt->right);
    }
}

int search(tree_type *rt,char str[20])
{
      if(rt==NULL)
      {
          return 0;
      }

      if(strcmp(str,rt->info)==0)
      {
          return 1;
      }
      else
      {
           if(strcmp(str,rt->info)<0)
                 search(rt->left,str);
           else
                 search(rt->right,str);
      }
}

int main ()
{

    tree_type *root=NULL;
	unsigned i, j, k = 0;

	char linha[201], palavra[201];

	while (scanf(" %[^\n]", linha) != EOF)
	{
		i = j = 0;
		while (linha[i])
		{

			while (isalpha(linha[i]))
				palavra[j++] = tolower(linha[i++]);


			if (linha[i] == '\0')
			{
				palavra[j] = '\0';

				if (!search(root, palavra))
				    insert(&root, palavra);

				j = 0;

				memset(palavra, 0, sizeof(palavra));
				break;

			}

			palavra[j] = '\0';

			while (!isalpha(linha[i]))
			{
				i++;
				if (linha[i] == '\0')
					break;
			}

			if (!search(root, palavra))
				insert(&root, palavra);

			j = 0;
			memset(palavra, 0, sizeof(palavra));

		}

		memset(linha, 0, sizeof(linha));
	}
    
    display(root);


}