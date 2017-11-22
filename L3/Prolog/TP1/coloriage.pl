couleur(rouge).
couleur(jaune).
couleur(vert).
couleur(bleu).

couleur(C1,C2,C3,C4,C5,C6):-
  couleur(C1), couleur(C2), couleur(C3), couleur(C4), couleur(C5), couleur(C6),
  C1 \== C2, C1 \== C3, C1 \== C5, C1 \== C6,
  C2 \== C3, C2 \== C4, C2 \== C5, C2 \== C6,
  C3 \== C4, C3 \== C6,
  C5 \== C6.
