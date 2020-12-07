#include <stdio.h>
#include <stdlib.h>/* Тут почти реализованна функция добавления в дерево*/
#include <string.h>/* Посмотрите коментарии на строчках 92, 98 и 124 */

typedef void *Pointer;

typedef void (*Destructor)(Pointer data);

typedef void (*Enumeration)(const char *key, Pointer data, void *user);

typedef Pointer (*Updater)(Pointer old, Pointer next);


typedef struct Node {
    char *key;
    Pointer data;
    struct Node *parent;// Родитель
    struct Node *child;// Массив элементов идущих от данного элемента
    int *number_children;// Количество элементов идущих от данного элемента
} node;

typedef struct Trie {
    node root;
} trie;

int len_key(const char *key) {
    int i = 0;
    while (key[i] != '\0') {
        i++;
    }
    return i;
}

void print_key(const char* key){
    int len_k = len_key(key);
    int i = 0;
    while (i<=len_k){
        printf("%c", key[i]);
        i++;
    }
}

node create_node(char *key, Pointer data) {
    node n;
    n.key = malloc(sizeof(char) * len_key(key));
    memcpy(n.key, key, len_key(key));
    n.data = data;
    n.child = malloc(sizeof(node));
    int number_children = 0;
    n.number_children = &number_children;
    return n;
};

trie trie_created() {
    trie tr;
    node root;
    root.child = malloc(sizeof(Pointer));
    int number_children = 0;
    root.number_children = &number_children;
    root.key = "";
    tr.root = root;
    return tr;
};

int find_node_set(node n, const char *key) {/*Находим номер(начиная от 0) ребенка, с которым
 * у нас совпадает какая-то начальная часть key(может совпадать весь) */
    int i = 0;
    int len_n_k = len_key(n.key);
    while (i + 1 <= *(int*)n.number_children) {
        if (n.child[i].key[len_n_k] == key[len_n_k]) {
            return i;
        }
        i++;
    }
    return -1;
};

int trie_set(trie tr, char *key, Pointer data) {
    int i = 0;
    node n = tr.root;
    int max_i = len_key(key);
    while (i <= max_i) {
        if (*(int *) n.number_children == 0) {
            while (i < max_i) {
                char *intermediate_key = malloc(sizeof(char) * (i + 1));
                memcpy(intermediate_key, key, i + 1);
                int intermediate_data = 0;
                n.child[0] = create_node(intermediate_key, &intermediate_data);
                print_key(n.child[0].key);
                printf(" %d\n", *(int*)n.child[0].data);
                int number_children = *(int *) n.number_children + 1;
                n.number_children = &number_children;//Почему-то увеличивается только у n, а у того к чему мы
                // прировняли n до этого не увеличивается
                n = n.child[0];
                i++;
            }
            //    n.data = data;
            memcpy(n.data, data, sizeof(Pointer));//Если сразу загонять слово, то data присваевается самому
            // "верхнему", хотя должна к "нижнему"
            return 0;
        }
        int finder_node = find_node_set(n, key);
        if (finder_node == -1) {
            int number_children = *(int *) n.number_children + 1;
            n.number_children = &number_children;
            n.child = realloc(n.child, *(int *) n.number_children);
            n.child[*(int *) n.number_children - 1] = create_node(key, data);
            return 0;
        } else {
            n = n.child[finder_node];
            i++;
        }
    }
//    n.data = data;
    memcpy(n.data, data, sizeof(Pointer));
    return 0;
}

int main() {
    trie tr = trie_created();
    int abc = 12;
    int zxc = 100;
    trie_set(tr, "ted", &abc);
//    trie_set(tr, "A", &zxc);//Из-за того что не увеличивается number_children(на 92 строчке) у нас "t"
//    // перезаписывается на "A"
    print_key(tr.root.child[0].key);
    printf("%d\n", *(int *) tr.root.child[0].data);
//    printf("%d\n", *(int *) tr.root.child[1].data);
//    printf("%d\n", *(int *) tr.root.child[0].child[0].data);
//    printf("%d\n", *(int *) tr.root.child[0].child[0].child[0].data);
    return 0;
}

//int posimvolnoe_sravnenie(const char *key1, const char *key2) {
//    int i = 0;
//    while (key1[i] != '\0' || key2[i] != '\0') {
//        if (key1[i] != key2[i]) {
//            return i;
//        }
//        i++;
//    }
//    return -1;
//}

