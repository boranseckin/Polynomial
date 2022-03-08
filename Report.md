# Run Time and Space Complexities

## Poly
`S(n) = 8 (PolyNode *) + 4 (termsNo) = 12`

## PolyNode
`S(n) = 8 (PolyNode *) + 4 (deg) + 8 (coeff) = 20`

## deleteNode
`T(n) = n (while loop)`

`T(n) = Θ(n)`

`S(n) = 2 * (8 (PolyNode *)) = 16`

`S(n) = Θ(1)`

## addNode
`T(n) = n (while loop) + n (deleteNode)`

`T(n) = Θ(n)`

`S(n) = 8 (PolyNode *) + 16 (deleteNode) = 24`

`S(n) = Θ(1)`

## addMono
`T(n) = n (addNode)`

`T(n) = Θ(n)`

`S(n) = 8 (PolyNode *) + 28 (PolyNode) + 24 (addNode) = 60`

`S(n) = Θ(1)`

## addPoly
`T(n) = n (while loop) * n (addMono)`

`T(n) = Θ(n^2)`

`S(n) = 8 (PolyNode *) + 28 (PolyNode) + 24 (addNode) = 60`

`S(n) = Θ(1)`

## multiplyMono
`T(n) = n (while loop) * n (deleteNode)`

`T(n) = Θ(n^2)`

`S(n) = 8 (PolyNode *) + 16 (deleteNode) = 24`

`S(n) = Θ(1)`

## multiplyPoly
`T(n) = [n (1st while loop) * n (deleteNode)] + [n (2nd while loop) * n (3nd while loop) * n (addMono)] + [n (for loop) + n (addMono)]`

`T(n) = Θ(n^3)`

`S(n) = 2 * (8 (PolyNode *)) + 16 (deleteNode) + 2 * ((4 * n) (int *)) + 2 * (60 (addMono)) = 152 + 8n`

`S(n) = Θ(n)`

## duplicate
`T(n) = n (while loop) * n (addMono)`

`T(n) = Θ(n^2)`

`S(n) = 8 (PolyNode *) + 60 (addMono) = 68`

`S(n) = Θ(1)`

## getDegree
`T(n) = c`

`T(n) = Θ(1)`

`S(n) = 4 (int) = 4`

`S(n) = Θ(1)`

## getTermsNo
`T(n) = c`

`T(n) = Θ(1)`

`S(n) = 4 (int) = 4`

`S(n) = Θ(1)`

## evaluate
`T(n) = n (while loop)`

`T(n) = Θ(n)`

`S(n) = 8 (double) + 8 (PolyNode *) + 8 (return) = 24`

`S(n) = Θ(1)`
