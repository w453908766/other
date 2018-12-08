#lang racket


(define (zip list1 list0) (map cons list1 list0))
(define (seq lst)
  (define (rev i lst)
    (if (null? lst) '()
        (cons (cons i (car lst)) (rev (+ i 1) (cdr lst)))
   ))
  (rev 0 lst)
 )

(define (flat lst)
  (foldr append '() lst))


(define (range i n)
  (if (= i n) '()
      (cons  i (range (+ i 1) n))))


(define (iterate f n0) (stream-cons n0 (iterate f (f n0))))
(define ones (stream-cons 1 ones))
(define N (iterate (lambda (n) (+ 1 n)) 0))
(define (takes n s)
  (if (= n 0) '()
      (cons (stream-first s) (takes (- n 1) (stream-rest s)))
 ))


;;;;;;;;;;;;;;;;;;;;


(define (br-product brs1 brs0)
 (flat
  (map
 (lambda (br1) (map (lambda (br0) (cons br1 br0)) brs0))
 brs1)))







(define (brnums n)
  (if (= n 0) '(())
  (let* ((br-tab (takes n br-table))
         (br-tab-rev (reverse br-tab)))
     (flat (map br-product br-tab br-tab-rev))
  )))

(define br-table (stream-map brnums N))



(define (catalan-inc cat)
  (match cat
    [(cons n cn) (cons (+ n 1)(/ (* 2 cn (+ 1 (* 2 n))) (+ n 2)))]
    ))
(define catalan (stream-map cdr(iterate catalan-inc (cons 0 1))))



;(seq (brnums 5))
'((0 () () () () ()) (1 () () () (())) (2 () () (()) ())
 (3 () () (() ())) (4 () () ((()))) (5 () (()) () ())
 (6 () (()) (())) (7 () (() ()) ()) (8 () ((())) ())
 (9 () (() () ())) (10 () (() (()))) (11 () ((()) ()))
 (12 () ((() ()))) (13 () (((())))) (14 (()) () () ())
 (15 (()) () (())) (16 (()) (()) ()) (17 (()) (() ()))
 (18 (()) ((()))) (19 (() ()) () ()) (20 (() ()) (()))
 (21 ((())) () ()) (22 ((())) (())) (23 (() () ()) ())
 (24 (() (())) ()) (25 ((()) ()) ()) (26 ((() ())) ())
 (27 (((()))) ()) (28 (() () () ())) (29 (() () (())))
 (30 (() (()) ())) (31 (() (() ()))) (32 (() ((()))))
 (33 ((()) () ())) (34 ((()) (()))) (35 ((() ()) ()))
 (36 (((())) ())) (37 ((() () ()))) (38 ((() (()))))
 (39 (((()) ()))) (40 (((() ())))) (41 ((((()))))))



(define (SS xlen ylen)
  (if (= xlen 0) 0
  (let [(xlen-1 (- xlen 1))
        (ylen+1 (+ ylen 1))]
    (+ (SS xlen-1 ylen+1) (* (stream-ref catalan xlen-1) (stream-ref catalan ylen+1)))
    )))

(define (L bnum)
  (match bnum
    ['() 0]
    [(cons x y) (+ 1 (L x) (L y))]
    ))
                                               



(define (S bnum)
  (match bnum
    ['() 0]
    [(cons x y)
   (let [(xlen (L x))
         (ylen (L y))]
  
      (+ (SS xlen ylen) (* (S x) (stream-ref catalan ylen)) (S y))
    )]))



(define (logB br-num)
  (if (null? br-num) 0
  (if (not (null? (cdr br-num))) -1
  (let ((sub (logB (car br-num))))
    (if (= sub -1) -1
      (+ sub 1))))))


