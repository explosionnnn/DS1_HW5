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

struct Rec1 {
    int num;
    std::string name;
    std::string type1;
    int total;
    int hp;
    int atk;
    int def;
};


class BinarySearchTree {
    private:
        Bst *tree;
    public:
        BinarySearchTree() {
            tree = nullptr;
        }

        Bst* GetTree() {
            return tree;
        }

        Bst* GetRight() {
            return tree->right;
        }
        Bst* GetLeft() {
            return tree->left;
        }
        std::vector<Number> GetNode() {
            return tree -> list;
        }


        void SetTree(Bst* tree) {
            this -> tree = tree;
        }

        bool IsNull() {
            if (tree == nullptr) {
                return true;
            }
            return false;
        }

        int Height(Bst* t) {
            Bst* cur = t;
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

        Bst* FindMax(Bst *cur) {
            if (cur == nullptr) {
                return cur;
            }
            while (cur -> right != nullptr) {
                cur = cur -> right;
            }

            return cur;
        }

};

class System {
    private:
        std::vector<Main> main_list;
        int main_list_size;
        BinarySearchTree bst;
        int tree_height;
    public:
        System() {
            main_list_size = 0;
            tree_height = 0;
        }

        int binarySearch(int target) {
            int l = 0, r = main_list.size() - 1;

            while (l <= r) {
                int mid = l + (r - l) / 2;
                if (main_list[mid].num == target)
                    return mid;
                else if (main_list[mid].num < target)
                    l = mid + 1;
                else
                    r = mid - 1;
            }
            return -1; // 找不到
        }

        Bst* Add(int num, int hp, Bst *tree) {
            Bst *cur = bst.GetTree();
            if (cur == nullptr) { // i.e., BST points to "empty"
                Bst *new_node = new Bst;
                Number n = {num, hp};
                new_node -> left = nullptr;
                new_node -> right = nullptr;
                new_node -> list.push_back(n);
                cur = new_node;
                return cur;
            } else if (cur -> list[0].hp < hp) {
                cur -> right = Add(num, hp, cur -> left); // store A on the right subtree
                return cur;
            } else if (cur -> list[0].hp > hp) {
                cur -> left = Add(num, hp, cur -> right);
                return cur;
            } else if (cur -> list[0].hp == hp) {
                Number n = {num, hp};
                cur -> list.push_back(n);
                return cur;
            }
            return cur;
        }

        int FindInRange(int num1, int num2, Bst *tree, std::vector<int> &list) {
            Bst *cur = tree;
            int count = 0;
            int cur_hp = cur -> list[0].hp;

            if (num1 > cur_hp) {
                count += FindInRange(num1, num2, tree->right, list); //先找右
            }

            if (num1 <= cur_hp && num2 >= cur_hp) {
                for (int i = 0; i < cur -> list.size(); i++) {
                    list.push_back(cur -> list[0].num);
                }
            }

            if (num2 < cur_hp) {
                count += FindInRange(num1, num2, tree->left, list); //找左
            }

            return count;
        }

        void Task1() {
            ReadFile(); //havn't design
            Bst* cur = bst.GetTree();
            main_list_size = main_list.size();
            for (int i = 0; i < main_list_size; i++) {
                cur = Add(main_list[i].num, main_list[i].hp, cur);
            }
            bst.Height(bst.GetTree());
        }

        void Task2(int num1, int num2) {
            std::vector<int> list;
            int index;
            Bst* cur = bst.GetTree();
            if (num1 > num2) {
                int tmp = num2;
                num2 = num1;
                num1 = tmp;
            }
            int count_visited = FindInRange(num1, num2, cur, list);
            for (int i = 0; i < list.size(); i++) {
                index = binarySearch(list[i]);
                PrintTask2(main_list[index]); //hasn't design
            }
        }
};
