#include <cassert>
#include <iostream>
#include <filesystem>
#include <limits>
#include <vector>
#include <string>
#include <deque>
#include <numeric>
#include <functional>
#include <fstream>
#include <streambuf>

using namespace std;

namespace Strings {
	// split
	vector<string> split(const string& Line, const string& Coma){
		vector<string> ret;
		size_t coma_pos = 0;
		size_t coma_len = Coma.length();
		while(coma_pos != string::npos){
			size_t new_coma_pos = Line.find(Coma, coma_pos);
			if(new_coma_pos != string::npos){
				ret.push_back(Line.substr(coma_pos, new_coma_pos-coma_pos));
				coma_pos = new_coma_pos+coma_len;
			}else{
				ret.push_back(Line.substr(coma_pos, string::npos));
				coma_pos = string::npos;
			}
		}
		return ret;
	}

	// join
	struct join_with{
		string operator()(const string& S1, const string& S2){
			return (S1 + the_) + S2;
		}
		explicit join_with(const string& the) : the_(the){}
		private: 
		string the_;
	};
	
	string join(const vector<string>& Lines, const string& Coma){
		string ret;
		if(!Lines.empty()){
			join_with joiner = join_with(Coma);
			ret = Lines.front() + accumulate(Lines.begin()+1, Lines.end(), string(), joiner);
			return ret;
		}
		return ret;
	}

	// replace
	string replace(const string& Line, const string& Coma1, const string& Coma2){
		return join(split(Line, Coma1), Coma2);
	}
}

namespace Numbers {
	// unsigned calc routines
	string ensure_point(const string& S){
		if(S.find_first_of(',') == string::npos){
			return S+',';
		}else{
			return S;
		}
	}

	string ensure_minus(const string& S){
		if(S[0] != '-'){
			return "-"+S;
		}else{
			return S;
		}
	}

	string ensure_zero(const string& S){
		if(S == "-0"){
			return "0";
		}else{
			return S;
		}
	}

	string invert(const string& S){
		if(S[0] != '-'){
			return "-"+S;
		}else{
			return S.substr(1, string::npos);
		}
	}

	void align_to_each_other_with_0(const string& S1, const string& S2, string& NS1, string& NS2){
		size_t PL1 = S1.find_first_of(',');
		size_t PR1 = S1.length() - PL1;
		size_t PL2 = S2.find_first_of(',');
		size_t PR2 = S2.length() - PL2;
		size_t PLM = max(PL1, PL2);
		size_t PRM = max(PR1, PR2);

		NS1.assign(PLM+PRM+1, '0');
		NS1.replace(PLM-PL1+1, S1.length(), S1);
		NS2.assign(PLM+PRM+1, '0');
		NS2.replace(PLM-PL2+1, S2.length(), S2);
	}

	string trim_left(const string& S){
		string t = S.substr(S.find_first_not_of('0'), string::npos);
		if(t == ""){
			return "0";
		}
		if(t[0] == ','){
			return "0"+t;
		}
		return t;
	}

	string trim_right(const string& S){
		string t = S.substr(0, S.find_last_not_of('0') + 1);
		if(t[t.length()-1] == ','){
			return t.substr(0, t.length()-1);
		}
		return t;
	}

	string trim(const string& S){
		string s_or_null = trim_right(trim_left(S));
		if(s_or_null == ""){
			return "0";
		}else{
			return s_or_null;
		}
	}

	string us_add(const string& S1, const string& S2){
		string EPS1 = ensure_point(S1);
		string EPS2 = ensure_point(S2);

		string AS1, AS2;
		align_to_each_other_with_0(EPS1, EPS2, AS1, AS2);

		deque<char> Res;
		char Add = 0;

		string::reverse_iterator It1 = AS1.rbegin();
		string::reverse_iterator It2 = AS2.rbegin();
		string::reverse_iterator ItE1 = AS1.rend();
		for(; It1 != ItE1; ++It1, ++It2){
			if(*It1 == ','){
				Res.push_front(',');
			}else{
				char n = (*It1 -'0') + (*It2 -'0') + Add;
				if(n > 9){
					n -= 10;
					Add = 1;
				}else{
					Add = 0;
				}
				Res.push_front(n + '0');
			}
		}
		return trim( string(Res.begin(), Res.end()) );
	}

	string us_sub(const string& S1, const string& S2){
		string EPS1 = ensure_point(S1);
		string EPS2 = ensure_point(S2);
		string AS1, AS2, Sign;
		align_to_each_other_with_0(EPS1, EPS2, AS1, AS2);
		if(AS1.compare(AS2) < 0){
			AS1.swap(AS2);
			Sign = "-";
		}else{
			Sign = "";
		}

		deque<char> Res;
		char Sub = 0;

		string::reverse_iterator It1 = AS1.rbegin();
		string::reverse_iterator It2 = AS2.rbegin();
		string::reverse_iterator ItE1 = AS1.rend();
		for(; It1 != ItE1; ++It1, ++It2){
			if(*It1 == ','){
				Res.push_front(',');
			}else{
				char n = 10 + (*It1 -'0') - (*It2 -'0') - Sub;
				if(n > 9){
					n -= 10;
					Sub = 0;
				}else{
					Sub = 1;
				}
				Res.push_front(n + '0');
			}
		}
		return Sign + trim( string(Res.begin(), Res.end()) );
	}

	string us_mul1(const string& S, char C){
		char c = C - '0';
		string EPS = ensure_point(S);
		string AS = "0"+EPS;

		deque<char> Res;
		char Add = 0;

		string::reverse_iterator It = AS.rbegin();
		string::reverse_iterator ItE = AS.rend();
		for(; It != ItE; ++It){
			if(*It == ','){
				Res.push_front(',');
			}else{
				char n = (*It -'0') * c + Add;
				Add = n / 10;
				n = n % 10;
				Res.push_front(n + '0');
			}
		}
		return trim_right(string(Res.begin(), Res.end()));
	}

	string mul_10(const string& N){
		size_t point = N.find_first_of(',');
		if(point == string::npos){
			return N+"0";
		}else{
			string M=N;
			M[point] = M[point+1];
			M[point+1] = ',';
			return trim_right(M);
		}
	}

	string mul_10(const string& N, unsigned int P){
		if(P == 0){
			return N;
		}else{
			return mul_10(mul_10(N), P-1);
		}
	}

	string div_10(const string& N){
		size_t point = N.find_first_of(',');
		string M;
		if(point == string::npos){
			M = N + N[N.length()-1];
			M[N.length()-1] = ',';
		}else{
			M = N;
			M[point] = M[point-1];
			M[point-1] = ',';
		}

		if(M[0]==','){
			return "0"+M;
		}else{
			return M;
		}
	}

	string div_10(const string& N, unsigned int P){
		if(P == 0){
			return N;
		}else{
			return div_10(div_10(N), P-1);
		}
	}

	string us_mul(const string& S1, const string& S2){
		if(S1 == "0" || S2 == "0"){
			return "0";
		}
		if(S1.length() < S2.length()){
			return us_mul(S2, S1);
		}else{
			size_t point = S2.find_first_of(',');
			unsigned int shift;
			if(point == string::npos){
				shift = 0;
			}else{
				shift = S2.length() - point -1;
			}
			string CS2 = Strings::replace(S2, ".", "");
			string::reverse_iterator It = CS2.rbegin();
			string::reverse_iterator ItE = CS2.rend();
			vector<string> to_sum;
			to_sum.reserve(CS2.length());
			for(unsigned int i = 0; It != ItE; ++It, ++i){
				to_sum.push_back( mul_10( us_mul1(S1, *It), i));
			}
			return div_10( accumulate(to_sum.begin(), to_sum.end(), string("0"), us_add), shift);
		}
	}

	bool int_less(const string& S1, const string& S2){
		if(S1.length() < S2.length())return true;
		if(S1.length() > S2.length())return false;
		if(S1.compare(S2) < 0)return true;
		return false;
	}

	string int_div(const string& S1, const string& S2){
		if(int_less(S1, S2)){
			return "0";
		}

		string dmuls[10];
		dmuls[0] = "0";
		for(unsigned int i = 1; i <= 9; i++){
			dmuls[i] = us_mul1(S2, '0' + i);
		}

		string n = S1;
		string res;
		size_t l1 = S1.length();
		size_t l2 = S2.length();
		for(int i = l1-l2; i >= 0; i--){
			int j = 9;
			string to_subtract = "0";
			for(; j > 0 ; j--){
				to_subtract = trim_left(mul_10(dmuls[j], i));
				if(!int_less(n, to_subtract)){
					break;
				}
			}
			if(j>0){
				n = us_sub(n, to_subtract);
			}
			res += ('0'+j);
		}
		return trim_left(res);
	}

	string us_div(const string& S1, const string& S2){
		size_t point1 = S1.find_first_of(',');
		unsigned int after_point1 = (point1 == string::npos)? 0 : S1.length()-point1-1;
		size_t point2 = S2.find_first_of(',');
		unsigned int after_point2 = (point2 == string::npos)? 0 : S2.length()-point2-1;
		unsigned int max_after_point = max(after_point1, after_point2);
		string IS1 = mul_10(S1, max_after_point*2);
		string IS2 = mul_10(S2, max_after_point);
		return div_10( int_div(IS1, IS2), max_after_point);
	}


	// add sub mul div
	string add(const string& S1, const string& S2){
		if(S1 == "" || S2 == ""){
			cerr << ("Bad arguments: for addition \"" + S1 + "\" + \"" + S2 + "\"\n");
		}
		bool SN1 = S1[0] == '-';
		string US1 = SN1 ? S1.substr(1, string::npos) : S1;
		bool SN2 = S2[0] == '-';
		string US2 = SN2 ? S2.substr(1, string::npos) : S2;
		if( !SN1 && !SN2 ){
			return us_add(US1, US2);
		}else if( SN1 && !SN2 ){
			return us_sub(US2, US1);
		}else if( !SN1 && SN2 ){
			return us_sub(US1, US2);
		}else{
			return ensure_minus( us_add(US1, US2) );
		}
	}

	string sub(const string& S1, const string& S2){
		if(S1 == ""){
			cerr << ("Bad arguments: for subtraction \"" + S1 + "\" - \"" + S2 + "\"\n");
		}
		bool SN1 = S1[0] == '-';
		string US1 = SN1 ? S1.substr(1, string::npos) : S1;
		string RS2 = (S2=="") ? "0" : S2; // unary fix
		bool SN2 = RS2[0] == '-';
		string US2 = SN2 ? RS2.substr(1, string::npos) : RS2;
		if( !SN1 && !SN2 ){
			return us_sub(US1, US2);
		}else if( SN1 && !SN2 ){
			return ensure_minus( us_add(US2, US1) );
		}else if( !SN1 && SN2 ){
			return us_add(US1, US2);
		}else{
			return ensure_zero( invert( us_sub(US1, US2) ) );
		}
	}

	string mul(const string& S1, const string& S2){
		if(S1 == "" || S2 == ""){
			cerr << ("Bad arguments: for multiplication \"" + S1 + "\" * \"" + S2 + "\"\n");
		}
		if(S1 == "0" || S2 == "0"){
			return "0";
		}
		bool SN1 = S1[0] == '-';
		string US1 = SN1 ? S1.substr(1, string::npos) : S1;
		bool SN2 = S2[0] == '-';
		string US2 = SN2 ? S2.substr(1, string::npos) : S2;
		if( (!SN1 && !SN2) || (SN1 && SN2) ){
			return us_mul(US1, US2);
		}else{
			return ensure_minus( us_mul(US1, US2) );
		}
	}

	string div(const string& S1, const string& S2){
		if(S1 == "" || S2 == ""){
			cerr << ("Bad arguments: for division \"" + S1 + "\" / \"" + S2 + "\"\n");
		}
		if(S1 == "0"){
			return "0";
		}
		if(S2 == "0"){
			cerr << ("Bad arguments: zero division in calculating: \"" + S1 + "\" / \"" + S2 + "\"\n");
		}
		bool SN1 = S1[0] == '-';
		string US1 = SN1 ? S1.substr(1, string::npos) : S1;
		bool SN2 = S2[0] == '-';
		string US2 = SN2 ? S2.substr(1, string::npos) : S2;
		if( (!SN1 && !SN2) || (SN1 && SN2) ){
			return us_div(US1, US2);
		}else{
			return ensure_zero( ensure_minus( us_div(US1, US2) ) );
		}
	}

	bool is_a_number(const string& S) {
		if(S.empty())
			return false;
		if(S == "-")
			return false;
		if((S[0] >= '0' && S[0] <= '9') || S[0] == '-') { // starts with -, 0..9
			auto comas = 0u;
			for(size_t i = 1u; i < S.size(); ++i) {
				if(S[i] == ',') {
					comas++;
					if(comas > 1)
						return false;
				} else if(S[i] >= '0' && S[i] <= '9') {
				} else {
					return false;
				}
			}
			return true;
		} 
		return false;
	}
}

struct The {
	bool is_leaf = true;
	char leaf = 0x00;
	vector<The> branches;
};

int rank_of(const The& could_be_a_tensor) {
	if(could_be_a_tensor.is_leaf) // leaf
		return 0;
	if(could_be_a_tensor.branches.empty()) // empty list
		return 1;
	return 1 + rank_of(could_be_a_tensor.branches[0]); // tensor
}

string to_string(const The& a, int level = 0) {
	if(a.is_leaf) // letter to string
		return string() + a.leaf;

	string output;

	if(rank_of(a) == 1) {	// padding
		for(auto i = 0; i < level; ++i)
			output += '\t';
	}
	for(const The& branch: a.branches) { // strings
		output += to_string(branch, level + 1);
	}
	output += '\n';
	return output;
}

string rank_1_to_string(const The& a) {
	if(rank_of(a) != 1) {
		cerr << "Argument error: rank of the string-convertible structure should be 1\n";
		return string();
	}
	string output;
	for(const auto& b: a.branches) {
		output += b.leaf;
	}
	return output;
}

The string_to_rank_1(const string& s) {
	The a;
	a.is_leaf = false;
	a.branches.resize(s.size());
	for(auto i = 0u; i < s.size(); ++i) {
		a.branches[i].leaf = s[i];
	}
	return a;
}

vector<string> rank_2_to_strings(const The& a) {
	vector<string> output;
	if(rank_of(a) != 2) {
		cerr << "Argument error: rank of the string-array-convertible structure should be 2\n";
		return output;
	}
	for(const auto& b: a.branches) {
		output.push_back(rank_1_to_string(b));
	}
	return output;
}

The strings_to_rank_2(const vector<string>& ss) {
	The a;
	a.is_leaf = false;
	a.branches.resize(ss.size());
	for(auto i = 0u; i < ss.size(); ++i) {
		a.branches[i] = string_to_rank_1(ss[i]);
	}
	return a;
}

The binary_rank_to_rank(const The& left, const The& right, int left_rank, int right_rank, function<The (const The&, const The&)> f2) {
	if(rank_of(left) == left_rank && rank_of(right) == right_rank) {
		return f2(left, right);
	} else if(rank_of(left) == left_rank){
		The a;
		a.is_leaf = false;
		for(auto b: right.branches) {
			a.branches.push_back(binary_rank_to_rank(left, b, left_rank, right_rank, f2));
		}
		return a;
	}else if(rank_of(right) == right_rank){
		The a;
		a.is_leaf = false;
		for(auto b: left.branches) {
			a.branches.push_back(binary_rank_to_rank(b, right, left_rank, right_rank, f2));
		}
		return a;
	} else {
		if(left.branches.size() != right.branches.size()) {
			cerr << "Rank error in a binary operation: argument sizes don't match.\n";
			return The();
		}
		const auto element_count = left.branches.size();
		The a;
		a.is_leaf = false;
		for(auto i = 0; i < element_count; ++i) {
			const auto lb = left.branches[i];
			const auto rb = right.branches[i];
			a.branches.push_back(binary_rank_to_rank(lb, rb, left_rank, right_rank, f2));
		}
		return a;
	}
}

// for most operations like "+" or "split"
The binary_1_to_1(const The& left, const The& right, function<The (const The&, const The&)> f2) {
	return binary_rank_to_rank(left, right, 1, 1, f2);
}

// for things like "join"
The binary_2_to_1(const The& left, const The& right, function<The (const The&, const The&)> f2) {
	return binary_rank_to_rank(left, right, 2, 1, f2);
}

// exclusively V (filter)
The filtered(const The& left, const The& right) {
	if(rank_of(left) == 2 && rank_of(right) == 2) {
		The result;
		result.is_leaf = false;
		if(left.branches.size() != right.branches.size()) {
			cerr << "Rank error in V: filter size don't match the size of the filtered array.\n";
			return The();
		}
		for(size_t i = 0u; i < left.branches.size(); ++i) {
			if(right.branches[i].branches.size() != 1) {
				cerr << "Filter error in V: filter values shoud be either '0' or '1' exclusively. A value of rank " << rank_of(right.branches[i]) << " found instead.\n";
				return The();
			}
			if(right.branches[i].branches[0].leaf == '1') {
				result.branches.push_back(left.branches[i]);
			} else if(right.branches[i].branches[0].leaf == '0') {
				// don't push back
			} else {
				cerr << "Filter error in V: filter values shoud be either '0' or '1' exclusively. A value of '" << right.branches[i].branches[0].leaf << "' found instead.\n";
				return The();
			}
		}
		return result;
	} else if(rank_of(left) == 2){
		The a;
		a.is_leaf = false;
		for(auto b: right.branches) {
			a.branches.push_back(filtered(left, b));
		}
		return a;
	}else if(rank_of(right) == 2){
		The a;
		a.is_leaf = false;
		for(auto b: left.branches) {
			a.branches.push_back(filtered(b, right));
		}
		return a;
	} else {
		The a;
		a.is_leaf = false;
		for(auto lb: left.branches) {
			The la;
			la.is_leaf = false;
			for(auto rb: right.branches) {
				la.branches.push_back(filtered(lb, rb));
			}
			a.branches.push_back(la);
		}
		return a;
	}
}

// unary operations
The unary_rank(const The& the, int rank, function<The (const The&)> f1) {
	if(rank_of(the) == rank){
		return f1(the);
	} else {
		The a;
		a.is_leaf = false;
		for(auto b: the.branches) {
			a.branches.push_back(unary_rank(b, rank, f1));
		}
		return a;
	}
}

// e.g. for file load
The unary_1(const The& the, function<The (const The&)> f1) {
	return unary_rank(the, 1, f1);
}

// does all the tree consist of "Booleans"?
bool invertable(const The& t) {
	if(t.is_leaf) {
		if(t.leaf == '0' || t.leaf == '1')
			return true;
		else
			return false;
	} else {
		for(auto& b: t.branches)
			if(!invertable(b))
				return false;
		return true;
	}
}

// invert all the tree (given that it does consist of "Booleans")
void invert(The& t) {
	if(t.is_leaf) {
		if(t.leaf == '1')
			t.leaf = '0';
		else
			t.leaf = '1';
	} else {
		for(auto& b: t.branches)
			invert(b);
	}
}

// remove all but the targeted by index element for selected depth
void select_by_index_and_depth(The& the, int index, int depth) {
	if(depth == 0) {
		if(the.branches.size() <= index) {
			cerr << "Index error: select by index and depth found a branch with not enough branches\n";
			return;
		}
		the = the.branches[index];
	}
	for(auto& branch : the.branches)
		select_by_index_and_depth(branch, index, depth-1);
}

void tests();

// dispatch the operation
void execute(The& left, The& right) {
	if(left.branches.empty())
		return; // we're done!
	
	if(left.branches.back().is_leaf && left.branches.back().leaf == '_') {
		left.branches.pop_back();
		if(right.branches.size() < 1) {
			cerr << "Syntax error: the command has 0 no arguments\n";
			return;
		}
		if(!right.branches.back().is_leaf) {
			cerr << "Syntax error: a tensor can't be the command's argument\n";
			return;
		}
		if(right.branches.back().leaf == '.') { // exit
			right.branches.pop_back();
			return;
		}
		// non-return operations
		if(right.branches.back().leaf == 'U') { // underscore
			right.branches.back().leaf ='_';
			execute(left, right);
		} else if(right.branches.back().leaf == 'Z') { // slash
			right.branches.back().leaf ='/';
			execute(left, right);
		} else if(right.branches.back().leaf == 'N') { // backslash
			right.branches.back().leaf ='\\';
			execute(left, right);
		} else if(right.branches.back().leaf == 'J') { // line break
			right.branches.back().leaf = '\n';
			execute(left, right);
		} else if(right.branches.back().leaf == 'i') { // dot
			right.branches.back().leaf = '.';
			execute(left, right);
		} else if(right.branches.back().leaf == 'L') { // space
			right.branches.back().leaf = ' ';
			execute(left, right);
		} else if(right.branches.back().leaf == 'I') { // single quote
			right.branches.back().leaf = '\'';
			execute(left, right);
		} else if(right.branches.back().leaf == 'Y') { // double quote
			right.branches.back().leaf = '\"';
			execute(left, right);
		} else if(right.branches.back().leaf == '^') { // elevate all the last elements of the same rank
			right.branches.pop_back();
			if(right.branches.size() < 1) {
				cerr << "Syntax error: ^ has nothing to elevate\n";
				return;
			}
			The elevated;
			elevated.is_leaf = false;
			auto target_rank = rank_of(right.branches.back());
			int index_of_first_element_with_fitting_rank = right.branches.size() - 2;
			while(index_of_first_element_with_fitting_rank >= 0 && rank_of(right.branches[index_of_first_element_with_fitting_rank]) == target_rank) {
				--index_of_first_element_with_fitting_rank;
			}
			++index_of_first_element_with_fitting_rank;
			for(auto i = index_of_first_element_with_fitting_rank; i < right.branches.size(); ++i) {
				elevated.branches.push_back(right.branches[i]);
			}
			right.branches.erase(right.branches.begin() + index_of_first_element_with_fitting_rank, right.branches.end());
			right.branches.push_back(elevated);
			execute(left, right);
		} else if(right.branches.back().leaf == '|') { // put an element of the current branch on top by index
			right.branches.pop_back(); // throw away the bracket
			if(right.branches.size() < 1) {
				cerr << "Syntax error: ' operation (AKA atbitrary access) has no index\n";
				return;
			}
			const auto& index_container = right.branches.back();
			auto index = stoi(rank_1_to_string(index_container));
			right.branches.pop_back(); // throw away the index container
			right.branches.push_back(*(right.branches.rbegin() + index));
			execute(left, right);
		} else if(right.branches.back().leaf == '#') { // remove all but the targeted by index element for the selected depth
			right.branches.pop_back(); // throw away the bracket
			if(right.branches.size() < 2) {
				cerr << "Syntax error: \" operation (AKA select by index and depth) requires both index and depth arguments\n";
				return;
			}
			auto depth = stoi(rank_1_to_string(right.branches.back()));
			auto index = stoi(rank_1_to_string(right.branches[right.branches.size()-2]));
			right.branches.pop_back(); // throw away the depth container
			right.branches.pop_back(); // throw away the index container
			if(depth > 0)
				select_by_index_and_depth(right.branches.back(), index, depth-1);
			else
				select_by_index_and_depth(right, index, depth);
			execute(left, right);			
		} else if(right.branches.back().leaf == 'm') { // replicate an item multiple times
			right.branches.pop_back();
			if(right.branches.size() < 2) {
				cerr << "Syntax error: m operation (AKA replicate) need two arguments - an item to replicate and a number of replications\n";
				return;
			}
			auto item = right.branches[right.branches.size() - 2];
			auto n_replications = stoi(rank_1_to_string(right.branches[right.branches.size() - 1]));
			The replications;
			replications.is_leaf = false;
			for(auto i = 0; i < n_replications; ++i)
				replications.branches.push_back(item);
			right.branches.pop_back();
			right.branches.back() = replications;
			execute(left, right);
		} else if(right.branches.back().leaf == 'H') { // duplicate the last element
			right.branches.pop_back();
			if(right.branches.size() < 1) {
				cerr << "Syntax error: H operation (AKA dup) has no argument to duplicate\n";
				return;
			}
			right.branches.push_back(right.branches.back());
			execute(left, right);
		} else if(right.branches.back().leaf == 'X') { // drop the last element
			right.branches.pop_back();
			if(right.branches.size() < 1) {
				cerr << "Syntax error: X operation (AKA drop) has no argument to drop\n";
				return;
			}
			right.branches.pop_back();
			execute(left, right);
		} else if(right.branches.back().leaf == 'G') { // swap the last two elements
			right.branches.pop_back();
			if(right.branches.size() < 2) {
				cerr << "Syntax error: G operation (AKA swap) has not enough arguments to swap\n";
				return;
			}
			const auto last_branch = right.branches.size() - 1;
			swap(right.branches[last_branch], right.branches[last_branch - 1]);
			execute(left, right);
		} else if(right.branches.back().leaf == 'A') { // elevate an empty element
			right.branches.back().is_leaf = false;
			right.branches.back().branches.clear();
			execute(left, right);
		} else if(right.branches.back().leaf == '$') { // count
			right.branches.pop_back();
			if(right.branches.size() < 1) {
				cerr << "Syntax error: $ operation (AKA count) has no argument to count things into\n";
				return;
			}
			right.branches.back() = string_to_rank_1(to_string(right.branches.back().branches.size()));
			execute(left, right);
		} else if(right.branches.back().leaf == 'v') { // deelevate last element
			right.branches.pop_back();
			if(right.branches.size() < 1) {
				cerr << "Syntax error: v operation (AKA deelevate) has no argument to deelevate\n";
				return;
			}
			auto the_copy = right.branches.back();
			right.branches.pop_back();
			for(const auto& one_in_copy: the_copy.branches)
				right.branches.push_back(one_in_copy);
			execute(left, right);
		} else if(right.branches.back().leaf == '+') { // addition
			right.branches.pop_back();
			if(right.branches.size() < 2) {
				cerr << "Syntax error: binary operation + requires 2 arguments\n";
				return;
			}
			auto l = right.branches[right.branches.size() - 2];
			auto r = right.branches[right.branches.size() - 1];
			// computation goes to the left argument, the right one will be then popped
			right.branches[right.branches.size() - 2] = binary_1_to_1(l, r, [](const The& lt, const The& rt) -> The{
				auto ls = rank_1_to_string(lt);
				auto rs = rank_1_to_string(rt);
				return string_to_rank_1(Numbers::add(ls, rs));
			});
			
			right.branches.pop_back();
			execute(left, right);
		} else if(right.branches.back().leaf == '-') { // subtraction
			right.branches.pop_back();
			if(right.branches.size() < 2) {
				cerr << "Syntax error: binary operation - requires 2 arguments\n";
				return;
			}
			auto l = right.branches[right.branches.size() - 2];
			auto r = right.branches[right.branches.size() - 1];
			// computation goes to the left argument, the right one will be then popped
			right.branches[right.branches.size() - 2] = binary_1_to_1(l, r, [](const The& lt, const The& rt) -> The{
				auto ls = rank_1_to_string(lt);
				auto rs = rank_1_to_string(rt);
				return string_to_rank_1(Numbers::sub(ls, rs));
			});
			
			right.branches.pop_back();
			execute(left, right);
		} else if(right.branches.back().leaf == 'x') { // multiplication
			right.branches.pop_back();
			if(right.branches.size() < 2) {
				cerr << "Syntax error: binary operation x (AKA *) requires 2 arguments\n";
				return;
			}
			auto l = right.branches[right.branches.size() - 2];
			auto r = right.branches[right.branches.size() - 1];
			// computation goes to the left argument, the right one will be then popped
			right.branches[right.branches.size() - 2] = binary_1_to_1(l, r, [](const The& lt, const The& rt) -> The{
				auto ls = rank_1_to_string(lt);
				auto rs = rank_1_to_string(rt);
				return string_to_rank_1(Numbers::mul(ls, rs));
			});
			
			right.branches.pop_back();
			execute(left, right);
		} else if(right.branches.back().leaf == 'z') { // division
			right.branches.pop_back();
			if(right.branches.size() < 2) {
				cerr << "Syntax error: binary operation z (AKA /) requires 2 arguments\n";
				return;
			}
			auto l = right.branches[right.branches.size() - 2];
			auto r = right.branches[right.branches.size() - 1];
			// computation goes to the left argument, the right one will be then popped
			right.branches[right.branches.size() - 2] = binary_1_to_1(l, r, [](const The& lt, const The& rt) -> The{
				auto ls = rank_1_to_string(lt);
				auto rs = rank_1_to_string(rt);
				return string_to_rank_1(Numbers::div(ls, rs));
			});
			
			right.branches.pop_back();
			execute(left, right);
		} else if(right.branches.back().leaf == '=') { // equal?
			right.branches.pop_back();
			if(right.branches.size() < 2) {
				cerr << "Syntax error: binary operation = (AKA equal?) requires 2 arguments\n";
				return;
			}
			auto l = right.branches[right.branches.size() - 2];
			auto r = right.branches[right.branches.size() - 1];
			// computation goes to the left argument, the right one will be then popped
			right.branches[right.branches.size() - 2] = binary_1_to_1(l, r, [](const The& lt, const The& rt) -> The{
				auto ls = rank_1_to_string(lt);
				auto rs = rank_1_to_string(rt);
				return (ls == rs) ? string_to_rank_1("1") : string_to_rank_1("0");
			});
			right.branches.pop_back();
			execute(left, right);
		} else if(right.branches.back().leaf == '%') { // numerically equal?
			right.branches.pop_back();
			if(right.branches.size() < 2) {
				cerr << "Syntax error: binary operation % (AKA numerical equal?) requires 2 arguments\n";
				return;
			}
			auto l = right.branches[right.branches.size() - 2];
			auto r = right.branches[right.branches.size() - 1];
			// computation goes to the left argument, the right one will be then popped
			right.branches[right.branches.size() - 2] = binary_1_to_1(l, r, [](const The& lt, const The& rt) -> The{
				auto ls = rank_1_to_string(lt);
				auto rs = rank_1_to_string(rt);
				if(Numbers::is_a_number(ls) && Numbers::is_a_number(rs)) {
					auto difference = Numbers::sub(ls, rs);
					return (difference == "0") ? string_to_rank_1("1") : string_to_rank_1("0");
				} else {
					cerr << "Syntax error: binary operation % (AKA numerical equal?) requires 2 arguments to be number-interpretable\n";
					return The();
				}
			});
			right.branches.pop_back();
			execute(left, right);
		} else if(right.branches.back().leaf == '<') { // less?
			right.branches.pop_back();
			if(right.branches.size() < 2) {
				cerr << "Syntax error: binary operation < (AKA less) requires 2 arguments\n";
				return;
			}
			auto l = right.branches[right.branches.size() - 2];
			auto r = right.branches[right.branches.size() - 1];
			// computation goes to the left argument, the right one will be then popped
			right.branches[right.branches.size() - 2] = binary_1_to_1(l, r, [](const The& lt, const The& rt) -> The{
				auto ls = rank_1_to_string(lt);
				auto rs = rank_1_to_string(rt);
				if(Numbers::is_a_number(ls) && Numbers::is_a_number(rs)) {
					auto difference = Numbers::sub(ls, rs);
					return (difference[0] == '-') ? string_to_rank_1("1") : string_to_rank_1("0");
				} else {
					cerr << "Syntax error: binary operation < (AKA less) requires 2 arguments to be number-interpretable\n";
					return The();
				}
			});
			right.branches.pop_back();
			execute(left, right);
		} else if(right.branches.back().leaf == '>') { // greater?
			right.branches.pop_back();
			if(right.branches.size() < 2) {
				cerr << "Syntax error: binary operation > (AKA greater) requires 2 arguments\n";
				return;
			}
			auto l = right.branches[right.branches.size() - 2];
			auto r = right.branches[right.branches.size() - 1];
			// computation goes to the left argument, the right one will be then popped
			right.branches[right.branches.size() - 2] = binary_1_to_1(l, r, [](const The& lt, const The& rt) -> The{
				auto ls = rank_1_to_string(lt);
				auto rs = rank_1_to_string(rt);
				if(Numbers::is_a_number(ls) && Numbers::is_a_number(rs)) {
					auto difference = Numbers::sub(rs, ls);
					return (difference[0] == '-') ? string_to_rank_1("1") : string_to_rank_1("0");
				} else {
					cerr << "Syntax error: binary operation > (AKA greater) requires 2 arguments to be number-interpretable\n";
					return The();
				}
			});
			right.branches.pop_back();
			execute(left, right);
		} else if(right.branches.back().leaf == '(') { // substring?
			right.branches.pop_back();
			if(right.branches.size() < 2) {
				cerr << "Syntax error: binary operation ( (AKA substring) requires 2 arguments\n";
				return;
			}
			auto l = right.branches[right.branches.size() - 2];
			auto r = right.branches[right.branches.size() - 1];
			// computation goes to the left argument, the right one will be then popped
			right.branches[right.branches.size() - 2] = binary_1_to_1(l, r, [](const The& lt, const The& rt) -> The{
				auto ls = rank_1_to_string(lt);
				auto rs = rank_1_to_string(rt);
				return (rs.find(ls) != std::string::npos) ? string_to_rank_1("1") : string_to_rank_1("0");
			});
			right.branches.pop_back();
			execute(left, right);
		} else if(right.branches.back().leaf == ')') { // superstring?
			right.branches.pop_back();
			if(right.branches.size() < 2) {
				cerr << "Syntax error: binary operation ) (AKA superstring) requires 2 arguments\n";
				return;
			}
			auto l = right.branches[right.branches.size() - 2];
			auto r = right.branches[right.branches.size() - 1];
			// computation goes to the left argument, the right one will be then popped
			right.branches[right.branches.size() - 2] = binary_1_to_1(l, r, [](const The& lt, const The& rt) -> The{
				auto ls = rank_1_to_string(lt);
				auto rs = rank_1_to_string(rt);
				return (ls.find(rs) != std::string::npos) ? string_to_rank_1("1") : string_to_rank_1("0");
			});
			right.branches.pop_back();
			execute(left, right);
		} else if(right.branches.back().leaf == '[') { // string starts with?
			right.branches.pop_back();
			if(right.branches.size() < 2) {
				cerr << "Syntax error: binary operation [ (AKA string starts?) requires 2 arguments\n";
				return;
			}
			auto l = right.branches[right.branches.size() - 2];
			auto r = right.branches[right.branches.size() - 1];
			right.branches[right.branches.size() - 2] = binary_1_to_1(l, r, [](const The& lt, const The& rt) -> The{
				auto ls = rank_1_to_string(lt);
				auto rs = rank_1_to_string(rt);
				return (ls.find(rs) == 0) ? string_to_rank_1("1") : string_to_rank_1("0");
			});
			right.branches.pop_back();
			execute(left, right);
		} else if(right.branches.back().leaf == ']') { // string ends with?
			right.branches.pop_back();
			if(right.branches.size() < 2) {
				cerr << "Syntax error: binary operation ] (AKA string ends?) requires 2 arguments\n";
				return;
			}
			auto l = right.branches[right.branches.size() - 2];
			auto r = right.branches[right.branches.size() - 1];
			right.branches[right.branches.size() - 2] = binary_1_to_1(l, r, [](const The& lt, const The& rt) -> The{
				auto ls = rank_1_to_string(lt);
				auto rs = rank_1_to_string(rt);
				if (ls.length() >= rs.length()) {
					return (ls.compare(ls.length() - rs.length(), rs.length(), rs) == 0) ? string_to_rank_1("1") : string_to_rank_1("0");
				} else {
					return string_to_rank_1("0");
				}
			});
			right.branches.pop_back();
			execute(left, right);
		} else if(right.branches.back().leaf == 'T') { // Boolean not
			right.branches.pop_back();
			if(right.branches.size() < 1) {
				cerr << "Syntax error: binary operation T (AKA Boolean not) requires 1 argument\n";
				return;
			}
			if(!invertable(right.branches[right.branches.size() - 1])) {
				cerr << "Syntax error: binary operation T (AKA Boolean not) found a value which is not 1 neither 0\n";
				return;
			}
			invert(right.branches[right.branches.size() - 1]);
			execute(left, right);
		} else if(right.branches.back().leaf == 'W') { // Boolean and
			right.branches.pop_back();
			if(right.branches.size() < 2) {
				cerr << "Syntax error: binary operation W (AKA Boolean and) requires 2 arguments\n";
				return;
			}
			if(!invertable(right.branches[right.branches.size() - 1]) || !invertable(right.branches[right.branches.size() - 2])) {
				cerr << "Syntax error: binary operation W (AKA Boolean and) found a value which is not 1 neither 0\n";
				return;
			}
			auto l = right.branches[right.branches.size() - 2];
			auto r = right.branches[right.branches.size() - 1];
			right.branches[right.branches.size() - 2] = binary_1_to_1(l, r, [](const The& lt, const The& rt) -> The{
				auto ls = rank_1_to_string(lt);
				auto rs = rank_1_to_string(rt);
				if(ls == "1" && rs == "1")
					return string_to_rank_1("1");
				else
					return string_to_rank_1("0");
			});
			right.branches.pop_back();
			execute(left, right);
		} else if(right.branches.back().leaf == 'M') { // Boolean or
			right.branches.pop_back();
			if(right.branches.size() < 2) {
				cerr << "Syntax error: binary operation M (AKA Boolean or) requires 2 arguments\n";
				return;
			}
			if(!invertable(right.branches[right.branches.size() - 1]) || !invertable(right.branches[right.branches.size() - 2])) {
				cerr << "Syntax error: binary operation M (AKA Boolean or) found a value which is not 1 neither 0\n";
				return;
			}
			auto l = right.branches[right.branches.size() - 2];
			auto r = right.branches[right.branches.size() - 1];
			right.branches[right.branches.size() - 2] = binary_1_to_1(l, r, [](const The& lt, const The& rt) -> The{
				auto ls = rank_1_to_string(lt);
				auto rs = rank_1_to_string(rt);
				if(ls == "0" && rs == "0")
					return string_to_rank_1("0");
				else
					return string_to_rank_1("1");
			});
			right.branches.pop_back();
			execute(left, right);
		} else if(right.branches.back().leaf == 'C') { // interpret as number if possible, 0 otherwise
			right.branches.pop_back();
			if(right.branches.size() < 1) {
				cerr << "Syntax error: # operation (AKA interpret as number) has no argument to interpret\n";
				return;
			}
			right.branches.back() = unary_1(right.branches.back(), [](const The& the) -> The{
				auto value = rank_1_to_string(the);
				if(Numbers::is_a_number(value)) {
					// good!
					return the;
				} else {
					// also good
					return string_to_rank_1(string("0"));
				}
			});
			execute(left, right);			
		} else if(right.branches.back().leaf == '&') { // concatenate strings
			right.branches.pop_back();
			if(right.branches.size() < 2) {
				cerr << "Syntax error: binary operation & (AKA concatenation) requires 2 arguments\n";
				return;
			}
			auto l = right.branches[right.branches.size() - 2];
			auto r = right.branches[right.branches.size() - 1];
			right.branches[right.branches.size() - 2] = binary_1_to_1(l, r, [](const The& lt, const The& rt) -> The{
				auto ls = rank_1_to_string(lt);
				auto rs = rank_1_to_string(rt);
				return string_to_rank_1(ls + rs);
			});
			
			right.branches.pop_back();
			execute(left, right);
		} else if(right.branches.back().leaf == 'E') { // split a string
			right.branches.pop_back();
			if(right.branches.size() < 2) {
				cerr << "Syntax error: binary operation E (AKA split) requires 2 arguments\n";
				return;
			}
			auto l = right.branches[right.branches.size() - 2];
			auto r = right.branches[right.branches.size() - 1];
			// computation goes to the left argument, the right one will be then popped
			right.branches[right.branches.size() - 2] = binary_1_to_1(l, r, [](const The& lt, const The& rt) -> The{
				auto ls = rank_1_to_string(lt);
				auto rs = rank_1_to_string(rt);
				return strings_to_rank_2(Strings::split(ls, rs));
			});
			
			right.branches.pop_back();
			execute(left, right);
		} else if(right.branches.back().leaf == 'D') { // join strings
			right.branches.pop_back();
			if(right.branches.size() < 2) {
				cerr << "Syntax error: binary operation D (AKA join) requires 2 arguments\n";
				return;
			}
			auto l = right.branches[right.branches.size() - 2];
			auto r = right.branches[right.branches.size() - 1];
			// computation goes to the left argument, the right one will be then popped
			right.branches[right.branches.size() - 2] = binary_2_to_1(l, r, [](const The& lt, const The& rt) -> The{
				auto lss = rank_2_to_strings(lt);
				auto rs = rank_1_to_string(rt);
				return string_to_rank_1(Strings::join(lss, rs));
			});
			right.branches.pop_back();
			execute(left, right);
		} else if(right.branches.back().leaf == 'V') { // filter by a logical value
			right.branches.pop_back();
			if(right.branches.size() < 2) {
				cerr << "Syntax error: binary operation V (AKA filter) requires 2 arguments\n";
				return;
			}
			auto l = right.branches[right.branches.size() - 2];
			auto r = right.branches[right.branches.size() - 1];
			right.branches[right.branches.size() - 2] = filtered(l, r);
			right.branches.pop_back();
			execute(left, right);
		} else if(right.branches.back().leaf == 'b') { // load from file
			right.branches.pop_back();
			if(right.branches.size() < 1) {
				cerr << "Syntax error: b operation (AKA file loading) has no path to load from\n";
				return;
			}
			right.branches.back() = unary_1(right.branches.back(), [](const The& the) -> The{
				auto path = rank_1_to_string(the);
				if(filesystem::is_directory(path)) {
					vector<string> list;
					for (const auto & entry : filesystem::directory_iterator(path))
						list.push_back(entry.path());
					return strings_to_rank_2(list);
				} else {
					ifstream t(path);
					string content((std::istreambuf_iterator<char>(t)),
									std::istreambuf_iterator<char>());
					return string_to_rank_1(content);
				}
			});
			execute(left, right);
		} else if(right.branches.back().leaf == 'p') { // save to file
			right.branches.pop_back();
			if(right.branches.size() < 1) {
				cerr << "Syntax error: p operation (AKA file storing) requires 2 arguments\n";
				return;
			}
			auto l = right.branches[right.branches.size() - 2];
			auto r = right.branches[right.branches.size() - 1];
			// write to file, discard the returned The
			binary_1_to_1(l, r, [](const The& lt, const The& rt) -> The{
				auto what = rank_1_to_string(lt);
				auto where = rank_1_to_string(rt);
				std::ofstream out(where);
				out << what;
				out.close();
				return The();
			});
			right.branches.pop_back();
			execute(left, right);
		} else if(right.branches.back().leaf == 'o') { // delete file
			right.branches.pop_back();
			if(right.branches.size() < 1) {
				cerr << "Syntax error: o operation (AKA delete file) has no path to delete\n";
				return;
			}
			unary_1(right.branches.back(), [](const The& the) -> The{
				auto path = rank_1_to_string(the);
				if(filesystem::is_directory(path)) {
					filesystem::remove_all(path);
				} else {
					filesystem::remove(path);
				}
				return The();
			});
			right.branches.pop_back();
			execute(left, right);
		} else if(right.branches.back().leaf == 'e') { // help
			cout << "This is the nameless programming language.\n\n";
			cout << "Running the tests...\n";
			tests();
			cout << "All tests pass.\n";
			cout << "Rename this executable into a valid program and run it again.";
			right.branches.clear();
		} else {
			cerr << "The command doesn't know what " << right.branches.back().leaf << " is supposed to mean\n";
			return;
		}
	} else {
		right.branches.push_back(left.branches.back());
		left.branches.pop_back(); 
		execute(left, right);
	}
}

string process_to_string(string in){
	The left;
	left.is_leaf = false;
	const auto in_size = in.size();
	left.branches.resize(in_size);
	// store chars in the reverse order
	for(auto i = 0u; i < in_size; ++i)
		left.branches[i].leaf = in[in_size - i - 1];

	The right;
	right.is_leaf = false;
	execute(left, right);
	return to_string(right);
}

bool equal_or_print(string a, string b, string c) {
	if(a.empty() && b.empty())
		return true;
	if(a.empty() && !b.empty()) {
		cout << "left < right; rigth: " << b << "\n";
		return false;
	}
	if(!a.empty() && b.empty()) {
		cout << "left > right; left: " << a << "\n";
		return false;
	}
	if(a[0] != b[0]) {
		cout << "\"" << c+a[0] << "\" != \"" << c+b[0] << "\"\n";
		cout << int(a[0]) << " != " << int(b[0]) << "\n";
		return false;
	}
	c += a[0];
	return equal_or_print(a.substr(1), b.substr(1), c);
}


void tests() {
	// comments, symbols
	assert(process_to_string("test1._comment") == "test1\n");
	assert(process_to_string("substitutes:U_Z_N_i_J_L_I_Y_") == "substitutes:_/\\.\n \'\"\n");

	// elevation, deelevation, replication
	assert(process_to_string("test^_2^_") == "\ttest\n\t2\n\n");
	assert(process_to_string("test^_2^_^_v_") == "\ttest\n\t2\n\n");
	assert(process_to_string("test^_3^_m_") == "\t\ttest\n\t\ttest\n\t\ttest\n\n\n");

	// indexes
	assert(process_to_string("1^_2^_3^_2^_|_") == "\t1\n\t2\n\t3\n\t1\n\n");
	assert(process_to_string("1^_2^_3^_2^_0^_#_") == "3\n");
	assert(process_to_string("1^_2^_3^_^_2^_1^_#_") == "\t3\n\n");
	assert(process_to_string("1^_2^_3^_^_4^_5^_6^_^_^_2^_2^_#_") == "\t\t3\n\t\t6\n\n\n");

	// + - * /
	assert(process_to_string("2^_3^_+_") == "\t5\n\n");
	assert(process_to_string("4^_3^_-_") == "\t1\n\n");
	assert(process_to_string("4^_3^_x_") == "\t12\n\n");
	assert(process_to_string("12^_3^_z_") == "\t4\n\n");
	assert(process_to_string("1^_2^_^_3^_+_") == "\t\t4\n\t\t5\n\n\n");
	assert(process_to_string("1^_2^_^_3^_4^_^_+_") == "\t\t4\n\t\t6\n\n\n");

	// strings
	assert(process_to_string("pre,the,post^_,^_E_") == "\t\tpre\n\t\tthe\n\t\tpost\n\n\n");
	assert(process_to_string("pre,the,post^_,^_E_H_&_") == "\t\tprepre\n\t\tthethe\n\t\tpostpost\n\n\n");
	assert(process_to_string("pre,the,post^_,^_E_-^_D_") == "\tpre-the-post\n\n");
	assert(process_to_string("pre,the,post^_,^_E_H_p^_)_V_") == "\t\tpre\n\t\tpost\n\n\n");
	assert(process_to_string("pre,the,post^_,^_E_A_D_") == "\tprethepost\n\n");
	assert(process_to_string("pre,,post^_,^_E_A_D_") == "\tprepost\n\n");
	assert(process_to_string("pre1,123,4post^_,^_E_C_v_") == "\t0\n\t123\n\t0\n\n");

	// files
	assert(process_to_string("build.sh^_b_J_^_E_H_rm^_)_V_$_") == "\t1\n\n");
	assert(process_to_string(".^_b_H_build.sh^_)_V_$_") == "\t1\n\n");
	assert(process_to_string("test^_test.txt^_p_test.txt^_b_=_test.txt^_o_") == "\t1\n\n");

	// stack
	assert(process_to_string("1^_2^_3^_^_$_") == "\t3\n\n");
	assert(process_to_string("1^_2^_3^_H_") == "\t1\n\t2\n\t3\n\t3\n\n");
	assert(process_to_string("1^_2^_3^_X_") == "\t1\n\t2\n\n");
	assert(process_to_string("1^_2^_3^_G_") == "\t1\n\t3\n\t2\n\n");

	// logic
	assert(process_to_string("1,2^_1,2^_=_") == "\t1\n\n");
	assert(process_to_string("1,2^_2,2^_=_") == "\t0\n\n");
	assert(process_to_string("1,2^_1,20^_%_") == "\t1\n\n");
	assert(process_to_string("1,2^_2,20^_%_") == "\t0\n\n");
	assert(process_to_string("alice^_alice^_=_") == "\t1\n\n");
	assert(process_to_string("alice^_bob^_=_") == "\t0\n\n");
	assert(process_to_string("alice^_alice^_=_T_") == "\t0\n\n");
	assert(process_to_string("alice^_bob^_=_T_") == "\t1\n\n");
	assert(process_to_string("1,2^_2,2^_<_") == "\t1\n\n");
	assert(process_to_string("3,2^_2,2^_<_") == "\t0\n\n");
	assert(process_to_string("1^_1^_W_") == "\t1\n\n");
	assert(process_to_string("1^_0^_W_") == "\t0\n\n");
	assert(process_to_string("0^_1^_W_") == "\t0\n\n");
	assert(process_to_string("0^_0^_W_") == "\t0\n\n");
	assert(process_to_string("1^_1^_M_") == "\t1\n\n");
	assert(process_to_string("1^_0^_M_") == "\t1\n\n");
	assert(process_to_string("0^_1^_M_") == "\t1\n\n");
	assert(process_to_string("0^_0^_M_") == "\t0\n\n");

	// substrings
	assert(process_to_string("b^_bob^_(_") == "\t1\n\n");
	assert(process_to_string("bob^_bob^_(_") == "\t1\n\n");
	assert(process_to_string("alice^_bob^_(_") == "\t0\n\n");
	assert(process_to_string("bob^_b^_)_") == "\t1\n\n");
	assert(process_to_string("bob^_bob^_)_") == "\t1\n\n");
	assert(process_to_string("alice^_bob^_)_") == "\t0\n\n");
	assert(process_to_string("bob^_bob^_[_") == "\t1\n\n");
	assert(process_to_string("alice^_bob^_[_") == "\t0\n\n");
	assert(process_to_string("bobcat^_bob^_[_") == "\t1\n\n");
	assert(process_to_string("bob^_bob^_]_") == "\t1\n\n");
	assert(process_to_string("alice^_bob^_]_") == "\t0\n\n");
	assert(process_to_string("catbob^_bob^_]_") == "\t1\n\n");
}

int main(int argc, char *argv[]){
	auto program = filesystem::path(argv[0]).filename();
	cout << process_to_string(program);
	cout << endl;
	return 0;
}
