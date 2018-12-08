#lang racket
(define (acc func . lst) (_acc func lst)) 
(define (_acc func lst)
  (if (eq? '() (cdr lst)) (car lst)
      (func (car lst) (_acc func (cdr lst)))
 ))


 (require (planet "sicp.ss" ("soegaard" "sicp.plt" 2 1)))
(define origin (make-vect 0 0))
(define space-painter (segments->painter '()))
(define vert-line (segments->painter (list (make-segment origin (make-vect 0 1)))))
(define hor-line (segments->painter (list (make-segment origin (make-vect 1 0)))))

(define (shrink k painter) ((transform-painter  origin
                     (make-vect k 0) (make-vect 0 k)) painter))


(define (rotate rad painter)
  (let ((sinrad (sin rad)) (cosrad (cos rad)))
  ((transform-painter origin (make-vect cosrad sinrad) (make-vect (- sinrad) cosrad)) painter)))

(define rad60 (/ pi.f 3))
(define -rad60 (/ pi.f -3))

(define (move x y painter) ((transform-painter (make-vect x y) (make-vect (+ x 1) y)
 (make-vect x (+ 1 y))) painter))

(define (paint-mid painter) (paint (move 0.5 0.5 painter)))

(define (snow-comb n snow-edge) (-snow-comb n (/ (* 2 pi.f) n) snow-edge))

(define (-snow-comb n rad snow-edge)
  (if (= n 0) space-painter
  (superpose snow-edge (rotate rad (-snow-comb (- n 1) rad snow-edge)))
))
(define (paint-snow snow k) (paint-mid (shrink 0.5 (snow-comb 6 (stream-ref snow k)))))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (snow-splay s)
  (let ((s/2 (shrink 1/2  s))
        (s/4 (shrink 1/3  s)))
    (superpose s/2
    (move 0 1/2 (acc superpose
                       s/2 (rotate rad60 s/4) (rotate -rad60 s/4)))
    )))
    

(define snow0 (stream-cons vert-line (stream-map snow-splay snow0)))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (koch s)
  (let ((shr ((shrink 1/3)  s)))
    (let ((left (superpose shr ((move 1/3 0) (rotate rad60 shr)))))
      (superpose left (flip-horiz left)))))


(define snow (stream-cons hor-line (stream-map koch snow)))
(define snow-snow (stream-map snow-comb snow)) 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


(define (kk s)
  (let ((s/2 (shrink 1/2 s)) (s/4 (shrink 1/4 s)))
    (move 0 0.5
    (acc superpose s/2 (rotate pi.f s/2)
     (rotate (* 1 rad60) s/4) (rotate (* 2 rad60) s/4)
   (rotate (* 4 rad60) s/4) (rotate (* 5 rad60) s/4))
  )))
               
      

(define ss (stream-cons vert-line (stream-map kk ss)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
