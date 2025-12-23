#include "minisearch.h"

int main(int argc, char *argv[])
{
    unsigned int K;
    char * docfile = check_program_args(argv, argc, K);
    double k1 = 1.2;
    double b = 0.75;

    cout << "---> Parameteres given <---" << endl;
    cout << "-> K = " << K << endl;
    cout << "-> docfile: " << docfile << endl << endl;

    FILE * fp = open_file(docfile);
    unsigned int nlines = get_number_of_lines(fp);

    char ** docs = (char**) malloc(nlines * sizeof(char *));
    unsigned int * docs_word_counter =
        (unsigned int*) malloc(nlines * sizeof(unsigned int));

    for(unsigned int i = 0; i < nlines; i++)
        docs[i] = NULL;

    bool parsing_err = parse_docs(docs, fp);
    fclose(fp);

    if (parsing_err)
    {
        delete_docs(docs, docs_word_counter, nlines);
        return 1;
    }

    my_trie * my_trie_ptr = new my_trie();

    unsigned int total_nwords =
        insert_docs_into_trie(my_trie_ptr, docs, docs_word_counter, nlines);

    cout << "-> Trie has been created !" << endl;
    cout << "-> Number of docs: " << nlines << endl;
    cout << "-> Number of total words: " << total_nwords << endl << endl;

    double avgdl = double(total_nwords) / double(nlines);

    const unsigned int TERMINAL_WIDTH = 80;

    while (1)
    {
        cout << "-> Please type a trie command.." << endl;

        char * cmd = read_str(3);
        if (strlen(cmd) == 0)
        {
            free(cmd);
            continue;
        }

        if (strcmp("/exit", cmd) == 0)
        {
            free(cmd);
            break;
        }

        unsigned int cmd_nwords;
        char ** cmd_words = strip_line_into_words(cmd, cmd_nwords);

        if (strcmp("/df", cmd_words[0]) == 0)
        {
            if (cmd_nwords == 1)
            {
                my_trie_ptr->print(0);
            }
            else if (cmd_nwords == 2)
            {
                posting_list * pl_ptr =
                    my_trie_ptr->search_word(cmd_words[1]);

                cout << cmd_words[1] << "  ";
                cout << (pl_ptr ? pl_ptr->get_size() : 0) << endl;
            }
            else
            {
                cout << "-! ERROR - too many arguments for /df !" << endl;
            }
        }
        else if (strcmp("/tf", cmd_words[0]) == 0)
        {
            if (cmd_nwords != 3)
            {
                cout << "-! ERROR - wrong number of arguments for /tf !" << endl;
            }
            else if (!is_number(cmd_words[1]))
            {
                cout << "-! ERROR - first argument must be a number !" << endl;
            }
            else
            {
                int doc_id = atoi(cmd_words[1]);
                posting_list * pl_ptr =
                    my_trie_ptr->search_word(cmd_words[2]);

                cout << doc_id << "  " << cmd_words[2] << "  ";
                cout << (pl_ptr ? pl_ptr->get_term_freq(doc_id) : 0) << endl;
            }
        }
        else if (strcmp("/search", cmd_words[0]) == 0)
        {
            if (cmd_nwords == 1)
            {
                cout << "-! ERROR - at least one query required !" << endl;
            }
            else
            {
                unsigned int nqs = (cmd_nwords > 11) ? 10 : cmd_nwords - 1;

                posting_list ** pl_array =
                    (posting_list**) malloc(nqs * sizeof(posting_list*));

                unsigned int unq_doc_ids_size = 0;
                unsigned int * unq_doc_ids =
                    get_unq_doc_ids(cmd_words, pl_array, my_trie_ptr,
                                    nqs, unq_doc_ids_size);

                print_k_docs(docs, cmd_words, unq_doc_ids,
                             docs_word_counter, pl_array,
                             unq_doc_ids_size, nqs,
                             avgdl, nlines, K, k1, b,
                             TERMINAL_WIDTH);

                free(pl_array);
                free(unq_doc_ids);
            }
        }
        else
        {
            cout << "-! ERROR - command not found !" << endl;
        }

        delete_cmd_words(cmd_words, cmd_nwords);
        free(cmd);
    }

    delete_docs(docs, docs_word_counter, nlines);
    delete my_trie_ptr;

    cout << endl << "-> Trie has been destroyed !" << endl;
    return 0;
}
