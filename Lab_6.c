#include<stdio.h>
#include<stdlib.h>

typedef struct Unit{
	long int value;
	struct Unit* left;
	struct Unit* right;
} Unit;

int returnHeight(const Unit* tr){
	long int l, r;
    if(tr != NULL){
        l = (tr->left  != NULL) ? returnHeight(tr->left)  : 0;
        r = (tr->right != NULL) ? returnHeight(tr->right) : 0;
        return ((l > r) ? l : r) + 1;
    }
    return 0;
}

int balanceFactor(Unit* curUnit){
	return (returnHeight(curUnit->right)-returnHeight(curUnit->left)); 
}

Unit *rotateRight(Unit* spinner){
	Unit* tmp=spinner->left;
	spinner->left=tmp->right;
	tmp->right=spinner;
	return tmp;
}
Unit *rotateLeft(Unit* spinner){
	Unit* tmp=spinner->right;
	spinner->right=tmp->left;
	tmp->left=spinner;
	return tmp;	
}
Unit *doBalance(Unit* tree){
	int curBalanceFactor=balanceFactor(tree);
	if(curBalanceFactor==2){
		if(balanceFactor(tree->right)<0){
			tree->right=rotateRight(tree->right);
		}
		return rotateLeft(tree);
	}
	if(curBalanceFactor==-2){
		if(balanceFactor(tree->left)>0){
			tree->left=rotateLeft(tree->left);
		}
		return rotateRight(tree);	
	}
	return tree;
}

/*Добавляет новый элемент и возвращает новое дерево*/
Unit *addUnit(int curValue, Unit** head){
	if(*head==NULL){
		Unit* newUnit=(Unit *)malloc(sizeof(Unit*));
		*head=newUnit;
		newUnit->left=NULL;
		newUnit->right=NULL;
		newUnit->value=curValue;
		/*printf("Privet %d\n",curValue);*/
	}
	else{
		if(curValue<(*head)->value){
			/*printf("Priv %d < %d\n",curValue,(*head)->value);*/
			(*head)->left=addUnit(curValue, &(*head)->left);
		}
		else{
			/*printf("Priv %d > %d\n",curValue,(*head)->value);*/
			(*head)->right=addUnit(curValue, &(*head)->right);
		}
		*head=doBalance(*head);
	}
	return(*head);
}

int main(){
	long int nodeNum;
	Unit* tree=NULL;
	long int curValue;
	scanf("%d",&nodeNum);
	for(int i=0;i<nodeNum;++i){
		scanf("%d",&curValue);
		tree=addUnit(curValue, &tree);
	}
	if(nodeNum==0){
		printf("%d",0);
		return 0;
	}
	long int deep=returnHeight(tree);
	printf("%d",deep);
	return 0;
}
