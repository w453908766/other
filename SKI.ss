(define (T exp)
	(if (atom? exp) exp
	(if (not (eq? (car exp) 'lambda)) (list (T (car exp)) (T (cadr exp)))
	(let ((x (cadr exp)) (E (caddr exp)))
	(if (atom? E) (if (eq? x E) 'I (list 'K  E))
	(if (eq? (car E) 'lambda) (T (list 'lambda x (T E)))
	(list (list 'S (T (list 'lambda x (car E)))) (T (list 'lambda x (cadr E))))
))))))
	
	
(T '(lambda x (lambda y (y x))))
