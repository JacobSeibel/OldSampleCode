addonetoeach(L1,L2) :- accAOTE(L1,[],L2).
accAOTE([],Acc,Acc).
accAOTE([H|T],Acc,L) :- N is H+1,append(Acc,[N],NewAcc), accAOT(T,NewAcc,L).
