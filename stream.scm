(define-syntax s-cons
	(syntax-rules()
	[(_ a d) (cons a (lambda () d))]
))
(define s-car car)
(define (s-cdr z)
	(let ((d (cdr z)))
	(if (pair? d) d
	(let ((v (d)))
	(set-cdr! z v)
	v)
)))
(define (s-add s0 s1)
	(s-cons (+ (s-car s0) (s-car s1)) (s-add (s-cdr s0) (s-cdr s1)))) 



(define (s-map f s)
	(s-cons (f (s-car s)) (s-map f (s-cdr s))))

(define time 0)	

(define (add1 x) 
	(set! time (+ 1 time))
	(+ x 1)
)
	
	
(define N  (s-cons 0 (s-map add1 N)))
(define (s-fmap fs s)
	(s-cons ((s-car fs) (s-car s)) (s-fmap (s-cdr fs) (s-cdr s))))


(define (stol len s)
	(if (= len 0) '()
	(cons (s-car s) (stol (- len 1) (s-cdr s)))
))

(define (g x) (+ 1 x))
(define (i x) 0)

(define commands (s-cons g (s-cons i (s-cons g 
			(s-cons g (s-cons g (s-cons i (s-cons g (s-cons i '())))))))))

(define rand (s-cons 0 (s-fmap commands rand)))



;(define (inp) (s-cons (read) (inp)))
;(define nums (inp))

;(define sums (s-cons 0 (s-add sums nums)))

(define cmd (s-cons 1 (s-cons 3 (s-cons #f (s-cons 5 (s-cons #f '()))))))


(define command (s-map (lambda (c) (if c (lambda (s) (cons c s)) (lambda (s) (cdr s)))) cmd))

(define s (s-cons '() (s-fmap command s))) 


