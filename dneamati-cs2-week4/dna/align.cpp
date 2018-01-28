//
//  align.cpp
//  dna_alignment
//
//  Created by Erika DeBenedictis on 1/27/13.
//  Copyright (c) 2014 California Institute of Technology. All rights reserved.
//
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// scoring values
#define GAP_SCORE -5
#define MISMATCH -1
#define MATCHING 2

/**
 * @brief Packages the score and instruction string the align function returns
 */
struct align_result {
    int score;      // score of this alignment
    string inst;    // instruction on how to align the inputs

    align_result(int s, string i) {
        this->score = s;
        this->inst = i;
    }
    align_result() {
        this->score = 0;
        this->inst = "";
    }
};

// memo_type will allow us to hash the string input to align
// with its output for memoization
typedef unordered_map<string, align_result> memo_type;

/**
 * @brief Calculates max of three align results
 */
align_result maxAlign(align_result gapS, align_result gapT, align_result same){
    align_result best = gapS;
    if (gapT.score > best.score)
        best = gapT;
    if (same.score > best.score)
        best = same;
    return best;
}


/**
 * @brief Determines a match between two characters.
 */
align_result match(char s1, char t1) {
    align_result match;

    if (s1 == t1 && s1 != '-') { // Match achieved 
        match.score = MATCHING;
        match.inst = '|';
        return match;
    }
    else if (s1 == '-') {
        match.score = GAP_SCORE;
        match.inst = 't';
        return match;
    }
    else if (t1 == '-') {
        match.score = GAP_SCORE;
        match.inst = 's';
        return match;
    }
    else {
        match.score = MISMATCH;
        match.inst = '*';
        return match;
    }
}


/**
 * @brief Function takes two strings, s and t, and produces an align_result
 * of the highest alignment score and its corresponding instruction str.
 */
align_result align(string s, string t, memo_type &memo) {
    // if this result is memoized, use recorded result
    string key = s + "," + t;
    if (memo.count(key) > 0){
      return memo[key];
    }

    align_result answer;

    // Base Case: s or t is empty
    if (s.empty() && !t.empty()) // s is empty but not t
    {
        answer.score = -5;
        answer.inst = 't';
        return answer;
    }
    else if (t.empty() && !s.empty()) // t is empty but not s
    {
        answer.score = -5;
        answer.inst = 's';
        return answer;
    }
    else if (t.empty() && s.empty()) // Both are empty
    {
        return answer;
    }

    // Case 1: Gap in s, start of t
    align_result gapS = align(s, t.substr(1, t.size()), memo);
    align_result matchGapS = match('-', t[0]);
    gapS.score = matchGapS.score + gapS.score;
    gapS.inst = matchGapS.inst + gapS.inst;

    // Case 2: Start of s, gap in t
    align_result gapT = align(s.substr(1, s.size()), t, memo);
    align_result matchGapT = match(s[0], '-');
    gapT.score = matchGapT.score + gapT.score;
    gapT.inst = matchGapT.inst + gapT.inst;

    // Case 3: Start of s and start of t
    align_result same = 
    align(s.substr(1, s.size()), t.substr(1, t.size()), memo);
    align_result matchSame = match(s[0], t[0]);
    same.score = matchSame.score + same.score;
    same.inst = matchSame.inst + same.inst;

    answer = maxAlign(gapT, gapS, same);

    /* Before you return your calculated  align_result object,
       memoize it like so:*/
    memo[key] = answer;

    return answer;
}

/**
 * @brief Wrapper function to print the results of align
 */
void DNA_align(string s, string t) {
    cout << endl << "Calling DNA align on strings " << s << ", " << t << endl;

    // create the memoization system
    memo_type memo;

    align_result answer = align(s, t, memo);
    string ans = answer.inst;
    int score = answer.score;

    // Printing section
    // line where string s will be printed, spaces inserted
    string line1 = "";
    // line where string t will be printed, spaces inserted
    string line2 = "";
    // description of the relationship between s and t here (* | s t)
    string line3 = "";

    int j = 0;      // running index in s
    int k = 0;      // running index in t

    cout << endl;

    for (unsigned int m = 0; m < ans.length(); m++) {
        // i is the next element in our instruction string ans
        string i = ans.substr(m, 1);

        // only in s
        if(i.compare("s") == 0){
            line1 += s[j]; j++;
            line2 += " ";
            line3 += "s";
        }

        // only in t
        else if (i.compare("t") == 0){
            line1 += " ";
            line2 += t[k]; k++;
            line3 += "t";
        }

        // mismatch
        else if (i.compare("*") == 0){
            line1 += s[j]; j++;
            line2 += t[k]; k++;
            line3 += "*";
        }

        // match
        else {
            line1 += s[j]; j++;
            line2 += t[k]; k++;
            line3 += "|";
        }
    }
    cout << line1 << endl << line2 << endl << line3 << endl;
    cout << "Score for this alignment: " << score << endl;
}

int main(){
    // some test cases to begin with
    DNA_align("",   "a");
    DNA_align("b",  "");
    DNA_align("a", "a");
    DNA_align("b",  "a");
    DNA_align("b",  "ba");
    DNA_align("ab", "ba");
    DNA_align("ab", "b");
    DNA_align("abc", "ac");
    DNA_align("abc", "adc");
    DNA_align("ACTGGCCGT", "TGACGTAA");
    DNA_align("abracadabra", "avada kedavra");

    string virusBAN15807;
    virusBAN15807 += (string) "aaatatattc aatatggaaa gaataaaaga actaagagat" +
    (string) "ttaatgtcac agtctcgcac" +
    (string) "tcgcgagata ctgacaaaaa ccactgtgga ccatatggcc ataatcaaga aatatacatc " +
    "gggaaggcag gagaagaatc ctgcccttag gatgaaatgg atgatggcaa tgaaatatcc " +
    "aattacagca gacaaaagga taatggagat gatcccggaa aggaatgagc aaggtcagac " +
    "cctttggagc aagacaaatg atgctggatc agacagagtg atggtatcac ctctggctgt " +
    "gacgtggtgg aacagaaatg gaccaacgac aagtacagtc cattatccaa aggtctataa " +
    "aaactatttt gaaaaggtcg aaaggctaaa acatggaacc ttcggccccg ttcacttccg " +
    "aaaccaggtt aaaatacgcc gcagggttga cataaaccca ggccatgcag atcttaatgc " +
    "taaagaagca caagatgtca taatggagat cgtattccca aacgaagttg gagccaggat " +
    "attgacatca gagtcacagt taactataac aaaggaaaag aaggaagagc tacaggactg " +
    "caaaattgcc cctttgatgg tggcatacat gttggagaga gaactggttc gcaaaaccag " +
    "attcctacca gtagttggcg ggacaagcag tgtgtatatc gaagtgttgc atttgaccca " +
    "agggacctgc tgggagcaaa tgtacacacc gggaggggaa gtgagaaatg atgacgttga " +
    "tcagagttta attatcgctg ctagaaatat tgttagaaga gcaacagtat cagcagaccc " +
    "gctggcttcg ctcttggaga tgtgccatag tacacaaatt ggcgggataa ggatggtgga " +
    "catccttaga caaaacccaa cagaagaaca agctgtggat atatgcaaag cagcaatggg " +
    "tctaaggatc agttcatcct tcagctttgg aggattcact ttcaaaagga caagtggatc " +
    "atctgtcaaa agggaggaag aaatgctcac cggcaacctt caaacattga aaataagagt " +
    "acatgaagga tatgaggaat tcacaatggt cgggcgaaga gcaacagcca ttctaaggaa " +
    "ggcaaccaga agactgatcc aactgatagt gagtgggaaa gacgagcaat caatcgccga " +
    "ggcaatcata gtggcaatgg tgttttcaca agaggattgc atgataaagg cagtaagagg " +
    "tgatttgaat tttgtcaaca gagcgaacca gcggctaaat cctatgcatc aactcctgag " +
    "gcatttccaa aaggatgcaa aggtgctgtt ccaaaactgg ggaattgaac ccattgacaa " +
    "tgtaatgggg atgatcggaa tattgcctga catgaccccc agcacagaga tgtcattgag " +
    "aggagtgaga gtcagtaaaa tgggagtaga tgaatattcc agtactgaga aagtggttgt " +
    "gagtattgat cgcttcttga gggtccggga ccagagggga aacgtactcc tgtctcctga " +
    "agaggttagt gaaacacagg gtacagagaa gctgacgata acttattcat cgtccatgat " +
    "gtgggaaatc aacggtccgg aatcagtgct agtcaacaca tatcaatgga tcattagaaa " +
    "ttgggaaact gtgaagattc aatggtccca agaccctaca atgctttaca ataagatgga " +
    "gtttgaaccc tttcaatccc tagtgcctaa ggctgccaga ggccaatata gtggatttgt " +
    "aaggatgcta ttccagcaga tgcgtgatgt gctggggaca tttgacactg tccaaataat " +
    "aaagctatta ccatttgcag cagccccacc ggagcagagc aggatgcagt tctcttctct " +
    "aactgtgaat gtgaggggtt caggaatgag aatacttgtg agaggcaatt ctcctgtgtt " +
    "caactacaac aaggcaacca agaggcttac agtacttgga aaggatgcag gtgcattgat " +
    "ggaagaccca gatgagggaa cagcaggagt ggaatctgcg gtattgagag gatttctgat " +
    "cctaggcaaa gaagacaaaa gatatgggcc agcattgagc atcaacgaat tgagcaatct " +
    "tgcgagaggg gagaaggcta atgtgctgat agggcaagga gacgtggtgt tggtaatgaa " +
    "acgaaaacgg gactctagca tacttactga cagccagaca gcgaccaaaa ggattcggat " +
    (string) "ggccatcaat tagtgttgaa ttgtttaaa";

    string virusBAN15814 = (string) "acaaaaacat aatggattcc aacactgtgt " +
    (string) "caagcttcca ggtagactgc tttctttggc" +
    (string) "atgtccgcaa acgatttgca gaccaagaac tgggtgatgc cccatttcta gatcggcttc " +
    "gccgagatca gaagtccctg agaggaagaa gcagcactct tggtctggac atcagaactg " +
    "ctactcgtga aggaaagcat atagtggaac ggattttaga ggacgagtca gatgaagcat " +
    "ttaaaatgag tattgcttca gtgccagctc cacgctatct aactgacatg actcttgaag " +
    "aaatgtcaag agattggtta atgctcattc ccaaacagaa agtggcaggg tccctttgca " +
    "ttagaatgga ccaagcaata gtggacaaaa aaatcacatt gaaagcaaat ttcagtgtga " +
    "ttttcaatcg acttgaagcc ctgatactac ttagagcttt tacggaagaa ggagcaattg " +
    "tgggcgaaat ctcaccatta ccttctcttc caggacatac tgacaaggat gtcaaaaatg " +
    "caattgaggt cctcatcgga gggtttgaat ggaatgataa cacagttcga gtctctgaaa " +
    "ctctacagag attcgcttgg agaagcagcg atgaggatgg gagacctcca ctctctacaa " +
    "agtagaaacg ggaaatggag agaacagcta agccagaaat tcgaagaaat aagatggttg " +
    "attgaagaag tacgacatag attaaagatt acggagaata gctttgagca aataactttt " +
    "atgcaagcct tacaactatt gcttgaagtg gagcaagaga taagaacttt ctcgtttcag " +
    "cttatttaat gataa";

    DNA_align( virusBAN15807, virusBAN15814); // NOTE FOR TA !!!!
    // Comment the line above for the program to run quickly. 
    // On the VM, the above worked with a score of 38, indicating
    // quite a bit of resemblance. 
    return 0;
}
