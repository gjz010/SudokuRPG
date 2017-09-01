#include "DancingLinkSolver.h"
#include <algorithm>
//#define DEBUG
#ifdef DEBUG
#include <cstdio>
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...)
#endif
struct Node {
    Node* left = this;
    Node* right = this;
    Node* up = this;
    Node* down = this;
    Node* col = this;
    int row = 0;
    int column = 0;
};
struct DancingLinkSolver::Internal {
    int* ans_stack;
    int* current;
    std::vector<int> ans;

    //std::vector<int> ans;
    Node* head;
    std::vector<Node*> col;
    std::vector<int> col_counter;
    std::vector<Node*> all_nodes;
    int row_count;
    int solutions = 0;
};


DancingLinkSolver::DancingLinkSolver(std::vector<std::vector<int> > vec, int col)
{
    debug("Lines:%d\n", vec.size());

    //system("pause");
    data = new Internal;
    data->row_count = vec.size();
    maxcol = col;
    data->ans_stack = new int[data->row_count];
    data->current = data->ans_stack;
    //Initialize the first line.
    data->head = new Node;
    data->all_nodes.push_back(data->head);
    Node* right_most = data->head;
    for (int i = 0; i < maxcol; i++) {
        Node* node = new Node;
        node->column = i + 1; //Debug purpose
        data->all_nodes.push_back(node);

        right_most->right = node;
        node->left = right_most;
        data->col.push_back(node);
        data->col_counter.push_back(0);
        right_most = node;
    }
    right_most->right = data->head;
    data->head->left = right_most;
    //Fill the whole dancing link.
    std::vector<Node*> col_last = data->col;
    for (int i = 0; i < vec.size(); i++) {
        Node* line = nullptr;
        Node* prev = nullptr;
        for (int j = 0; j < vec[i].size(); j++) {
            Node* node = new Node;
            data->all_nodes.push_back(node);
            int col_index = vec[i][j];
            data->col_counter[col_index]++;
            Node* col_last_node = col_last[col_index];
            col_last_node->down = node;
            node->up = col_last_node;
            node->down = data->col[col_index];
            node->col = data->col[col_index];
            data->col[col_index]->up = node;
            col_last[col_index] = node;
            node->row = i + 1;
            node->column = node->col->column;
            if (line == nullptr) {
                line = node;
            }
            else {
                node->left = prev;
                prev->right = node;
                node->right = line;
                line->left = node;
            }
            prev = node;
        }
    }

}
struct RestoreStack {
    Node* node;
    bool isLR;
    RestoreStack(Node* n, bool lr) :node(n), isLR(lr) {};

};
bool DancingLinkSolver::Solve()
{

    if (data->head->right == data->head) {
        data->solutions++;
        for (int* iter = data->ans_stack; iter != data->current; iter++) data->ans.push_back(*iter);
        return true;
    }
    Node* current_col = data->head->right;
    Node* column_selector = data->head->right;
    int tmp = 0x7fffffff;
    while (column_selector != data->head) {
        int score = data->col_counter[column_selector->column - 1];
        if (score < tmp) {
            tmp = score;
            current_col = column_selector;
        }
        column_selector = column_selector->right;
    }
    Node* column_iter = current_col->down;

    //std::vector<Node*> chosen_row;
    //chosen_row.reserve(data->row_count);
    //std::vector<RestoreStack> removed_element_stage1;
    //std::vector<RestoreStack> removed_element_stage2;
    //removed_element_stage1.reserve(1024);
    //removed_element_stage2.reserve(1024);
    debug("Phase 1 with col %d!\n", current_col->column);
    while (column_iter != current_col) {
        //chosen_row.push_back(column_iter);
        Node* row_iter = column_iter->right;
        while (row_iter != column_iter) {
            Node* up = row_iter->up;
            Node* down = row_iter->down;
            up->down = down;
            down->up = up;
            data->col_counter[row_iter->column - 1]--;
            debug("Deleting node in row %d column %d!\n", row_iter->row, row_iter->col->column);
            //removed_element_stage1.push_back(RestoreStack(row_iter,false));
            row_iter = row_iter->right;
        }
        column_iter = column_iter->down;
    }
    {
        Node* left = current_col->left;
        Node* right = current_col->right;
        left->right = right;
        right->left = left;

        debug("Deleting node in row %d column %d!\n", current_col->row, current_col->col->column);
        //removed_element_stage1.push_back(RestoreStack(current_col, true));
    }
    debug("Phase 2\n");
    Node* row = current_col->down;
    while (row != current_col) {
        debug("Pushing %d into stack\n", row->row);
        *(data->current++) = row->row;
        //data->ans.push_back(row->row);
        Node* row_iter = row->right;
        while (row_iter != row) {
            Node* column = row_iter->col;
            Node* col_iter = column->down;
            while (col_iter != column) {
                Node* new_row = col_iter->right;
                while (new_row != col_iter) {
                    Node* up = new_row->up;
                    Node* down = new_row->down;
                    up->down = down;
                    down->up = up;
                    data->col_counter[new_row->column - 1]--;
                    debug("Deleting node in row %d column %d!\n", new_row->row, new_row->col->column);
                    //removed_element_stage2.push_back(RestoreStack(new_row,false));
                    new_row = new_row->right;
                }
                col_iter = col_iter->down;
            }
            {
                Node* left = column->left;
                Node* right = column->right;
                left->right = right;
                right->left = left;
                debug("Deleting node in row %d column %d!\n", column->row, column->col->column);
                //removed_element_stage2.push_back(RestoreStack(column, true));
            }
            row_iter = row_iter->right;
        }
        bool result = Solve();
        if (false) {

            return true;
        }
        else { //Backtrack!
            if (data->solutions > 1) {
                return false;
            }
            debug("Backtracking phase 2!\n");
            {

                Node* row_rev_iter = row->left;
                while (row_rev_iter != row) {
                    Node* column = row_rev_iter->col;
                    {

                        Node* left = column->left;
                        Node* right = column->right;
                        left->right = column;
                        right->left = column;
                        debug("1:Restoring node in row %d column %d!\n", column->row, column->col->column);
                        //removed_element_stage2.push_back(RestoreStack(column, true));
                    }
                    Node* col_rev_iter = column->up;
                    while (col_rev_iter != column) {
                        Node* new_row = col_rev_iter->left;
                        while (new_row != col_rev_iter) {
                            Node* up = new_row->up;
                            Node* down = new_row->down;
                            up->down = new_row;
                            down->up = new_row;
                            data->col_counter[new_row->column - 1]++;
                            debug("Restoring node in row %d column %d!\n", new_row->row, new_row->col->column);
                            //removed_element_stage2.push_back(RestoreStack(new_row,false));
                            new_row = new_row->left;
                        }
                        col_rev_iter = col_rev_iter->up;
                    }

                    row_rev_iter = row_rev_iter->left;
                }

            }




            /*
            for (auto iter = removed_element_stage2.rbegin(); iter != removed_element_stage2.rend(); iter++) {
            RestoreStack& item = *iter;
            if (item.isLR) {
            Node* left = item.node->left;
            Node* right = item.node->right;
            left->right = item.node;
            right->left = item.node;
            }
            else {
            Node* up = item.node->up;
            Node* down = item.node->down;
            up->down = item.node;
            down->up = item.node;
            }
            }
            removed_element_stage2 = vector<RestoreStack>();
            */
            data->current--;
        }
        row = row->down;
    }
    //But no row came.
    debug("Backtracking phase 1!\n");



    {
        Node* left = current_col->left;
        Node* right = current_col->right;
        left->right = current_col;
        right->left = current_col;

        debug("Restoring node in row %d column %d!\n", current_col->row, current_col->col->column);
        //removed_element_stage1.push_back(RestoreStack(current_col, true));
    }
    Node* column_rev_iter = current_col->up;
    while (column_rev_iter != current_col) {
        Node* row_rev_iter = column_rev_iter->left;
        while (row_rev_iter != column_rev_iter) {
            Node* up = row_rev_iter->up;
            Node* down = row_rev_iter->down;
            up->down = row_rev_iter;
            down->up = row_rev_iter;
            data->col_counter[row_rev_iter->column - 1]++;
            debug("Restoring node in row %d column %d!\n", row_rev_iter->row, row_rev_iter->col->column);
            //removed_element_stage1.push_back(RestoreStack(row_iter,false));
            row_rev_iter = row_rev_iter->left;
        }
        column_rev_iter = column_rev_iter->up;
    }

    /*
    for (auto iter = removed_element_stage1.rbegin(); iter != removed_element_stage1.rend(); iter++) {
    RestoreStack item = *iter;
    if (item.isLR) {
    Node* left = item.node->left;
    Node* right = item.node->right;
    left->right = item.node;
    right->left = item.node;
    }
    else {
    Node* up = item.node->up;
    Node* down = item.node->down;
    up->down = item.node;
    down->up = item.node;
    }
    }
    */
    return false;
}

std::vector<int> DancingLinkSolver::ans()
{
    /*
    std::vector<int> ans;
    for (int* iter = data->ans_stack; iter != data->current; iter++) ans.push_back(*iter);
    return ans;
    */
    return data->ans;
}

DancingLinkSolver::~DancingLinkSolver()
{
    //Whiter than white!
    std::for_each(data->all_nodes.begin(), data->all_nodes.end(), [](Node* node) {
        delete node;
    });
    delete data;
}

void DancingLinkSolver::coverColumn(int col)
{
}

void DancingLinkSolver::uncoverColumn(int col)
{
}
