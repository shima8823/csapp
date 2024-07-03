/*

bool M_bubble = m_stat in { SADR, SINS, SHLT } || W_stat in { SADR, SINS, SHLT}
一つ上のパイプラインにWrite backステージがあるからW_statも見る。

bool W_stall  = W_stat in { SADR, SINS, SHLT}
こっちにはない

*/