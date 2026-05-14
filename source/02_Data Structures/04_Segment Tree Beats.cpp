ll ST1[4*N + 5], ST2[4*N + 5]; //MAX value, SUM Value
ll smax[4*N + 5], occ[4*N + 5];//2nd Max, occurence of 1st Max
ll arr[N + 5];

void pushup(int idx){
    ST1[idx] = max(ST1[2*idx], ST1[2*idx + 1]);
    ST2[idx] = ST2[2*idx] + ST2[2*idx + 1];
    if (ST1[2*idx] == ST1[2*idx + 1]){
        smax[idx]= max(smax[2*idx], smax[2*idx + 1]);
        occ[idx] = occ[2*idx] + occ[2*idx + 1];
    }
    else{
        smax[idx] = min(ST1[2*idx], ST1[2*idx + 1]);
        smax[idx] = max(smax[idx], max(smax[2*idx],smax[2*idx + 1]));
        if (ST1[2*idx] <= ST1[2*idx + 1])
            occ[idx] = occ[2*idx + 1];
        if (ST1[2*idx] > ST1[2*idx + 1])
            occ[idx]=occ[2*idx];
    }
}
void build(int idx, int l, int r){
    if (l == r){
        ST1[idx] = ST2[idx] = arr[l];
        occ[idx] = 1;
        smax[idx] = -1;
        return;
    }
    int mid = (l+r)>>1;
    build(2*idx, l, mid);
    build(2*idx + 1, mid + 1, r);
    pushup(idx);
}
void pushdown(int idx, ll v){
    if(ST1[idx] <= v) return;
    assert(v > smax[idx]);
    ST2[idx] -= (ll)(ST1[idx] - v) * (ll)occ[idx];
    ST1[idx] = v;
}
void down(int idx, ll v){
    pushdown(2*idx, v);
    pushdown(2*idx + 1, v);
}
void update(int idx, int l, int r, int le, int ri, ll v){
    //update min(Ai,t)
    if (r < le || ri < l || ST1[idx] <= v)
        return;
    if (le <= l && r <= ri && smax[idx] < v){
        pushdown(idx, v);
        return;
    }
    down(idx, ST1[idx]);
    int mid = (l+r)>>1;
    update(2*idx, l, mid, le, ri, v);
    update(2*idx + 1, mid + 1, r, le, ri, v);
    pushup(idx);
}
ll query1(int idx, int l, int r, int le, int ri){
    //sumquery
    if(r < le || ri < l) 
        return -1;
    if(le <= l && r <= ri) 
        return ST1[idx];
    down(idx, ST1[idx]);
    int mid = (l+r)>>1;
    ll resa = query1(2*idx, l, mid, le, ri);
    ll resb = query1(2*idx + 1, mid + 1, r, le, ri);
    return max(resa, resb);
}
ll query2(int idx, int l, int r, int le, int ri){
    //maxquery
    if(r < le || ri < l) 
        return 0;
    if(le <= l && r <= ri)
        return ST2[idx];
    down(idx, ST1[idx]);
    int mid = (l+r)>>1;
    ll resa = query2(2*idx, l, mid, le, ri);
    ll resb = query2(2*idx + 1, mid + 1, r, le, ri);
    return resa + resb;
}