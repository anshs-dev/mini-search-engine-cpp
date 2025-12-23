# Mini Search Engine (C++)

A lightweight **in-memory search engine** implemented in **C++**, designed to demonstrate the core components behind real-world search systems such as **inverted indexing**, **efficient lookup**, and **relevance-based ranking**. The project emphasizes **data structures, algorithmic efficiency, and system-level design**, rather than UI or external libraries.

## ✨ Features

- Builds an **inverted index** over a collection of text documents
- Supports **keyword-based search queries**
- Ranks documents using **BM25 relevance scoring**
- Retrieves **top-K most relevant documents**
- Fast word lookup using a **Trie**
- Fully **cross-platform** (Linux / Windows compatible)
- Implemented in **C++ without STL**

## 📥 Input Format

The application processes a document file (`docfile`) where **each line represents one document**.

Example:
```
0 The quick brown fox leaped over the lazy lazy dog
1 Quick brown foxes leaped over lazy dogs for fun
```

- The **first token** of each line is the document ID
- Document IDs must start from `0` and be **sequential**
- Input validation is performed and the program exits on errors

Sample datasets, queries, and expected results are provided in:
- `datasets/`
- `queries/`
- `results/`

## 🧱 Core Data Structures

### Document Store
A dynamically allocated array mapping document IDs to document text.

### Inverted Index
Maps each unique word to a posting list containing document IDs and term frequencies.

### Trie
A Trie (prefix tree) is used to efficiently locate posting lists for query terms.

## 📊 Relevance Scoring (BM25)

Documents are ranked using the BM25 ranking function with default parameters:
```
k1 = 1.2
b  = 0.75
```

## ▶️ Build & Run

Build:
```
make
```

Run:
```
./minisearch -i <docfile> -k <K>
```

## ⌨️ Application Commands

/search q1 q2 ... q10  
/df  
/df <word>  
/tf <doc_id> <word>  
/exit

## 👤 Author

Ansh Soni  
GitHub: https://github.com/anshs-dev  
LinkedIn: https://www.linkedin.com/in/anshs-dev
