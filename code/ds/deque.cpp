vector<int> st,ed;
void push_front(int x){st.pb(x);}
void push_back(int x){ed.pb(x);}
void rebuild(){
	
}
void rebuildfront(){
	int pos=(ed.size()+1)/2;
	for(int i=0;i<pos;i++)st.pb(ed[i]);
	reverse(st.begin(),st.end());
	reverse(ed.begin(),ed.end());
	for(int i=1;i<=pos;i++)ed.pop_back();
	reverse(ed.begin(),ed.end());
	rebuild();
}
void rebuildback(){
	int pos=(st.size()+1)/2;
	for(int i=0;i<pos;i++)ed.pb(st[i]);
	reverse(ed.begin(),ed.end());
	reverse(st.begin(),st.end());
	for(int i=1;i<=pos;i++)st.pop_back();
	reverse(st.begin(),st.end());
	rebuild();
}
int front(){
	if(!st.size())rebuildfront();
	return st.back();
}
int back(){
	if(!ed.size())rebuildback();
	return ed.back();
}
void pop_front(){
	if(!st.size())rebuildfront();
	st.pop_back();
}
void pop_back(){
	if(!ed.size())rebuildback();
	ed.pop_back();
}