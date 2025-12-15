#include<iostream>
#include<vector>
#include<string>

struct Number {
    int num;
    int hp;
};

struct Bst {
    std::vector<Number> list;
    Bst *right;
    Bst *left;
};

struct Main {
    int num;
    std::string name;
    std::string type1;
    std::string type2;
    int total;
    int hp;
    int atk;
    int def;
    int sp_atk;
    int sp_def;
    int speed;
    int generation;
    bool is_legend;
};

class System {
    private:
        std::vector<Main> main_list;
        int main_list_size;
        Bst *tree;
        int tree_height;
    public:
        System() {
            main_list_size = 0;
            tree_height = 0;
        }

        Bst* Add(int num, int hp, Bst *tree) {
            Bst *cur = tree;
            if (cur == nullptr) { // i.e., BST points to "empty"
                Bst *new_node = new Bst;
                Number n = {num, hp};
                new_node -> left = nullptr;
                new_node -> right = nullptr;
                new_node -> list.push_back(n);
                cur = new_node;
                return cur;
            } else if (cur -> list[0].hp < hp) {
                cur -> right = Add(num, hp, cur -> right); // store A on the right subtree
                return cur;
            } else if (cur -> list[0].hp > hp) {
                cur -> left = Add(num, hp, cur -> left);
                return cur;
            } else if (cur -> list[0].hp == hp) {
                Number n = {num, hp};
                cur -> list.push_back(n);
                return cur;
            }
            return cur;
        }

        int Height(Bst *tree) {
            Bst *cur = tree;
            if (cur == NULL) {
                return 0;
            }
            int right = Height(cur -> right);
            int left = Height(cur -> left);
            if (right > left) {
                return right+1;
            } else {
                return left+1;
            }
        }

        void Task1() {
            ReadFile(); //havn't design
            main_list_size = main_list.size();
            for (int i = 0; i < main_list_size; i++) {
                tree = Add(main_list[i].num, main_list[i].hp, tree);
            }
            tree_height = Height(tree);
        }
};
