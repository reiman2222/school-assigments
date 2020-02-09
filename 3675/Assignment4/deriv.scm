;Name: Jack Edwards
;Date: 10-13-17
;Tabs: 2

;deriv computes the derivative of expression E

(define (deriv E)
  (cond
    ((number? E) 0)
    ((symbol? E) 1)
    ((eq? (car E) '+) (list '+ (deriv (cadr E)) (deriv (caddr E))))
    ((eq? (car E) '-) (list '- (deriv (cadr E)) (deriv (caddr E))))
    ((eq? (car E) '*) (list '+ (list '* (cadr E) (deriv (caddr E)))
                               (list '* (deriv (cadr E)) (caddr E))))
    ((and (eq? (car E) '^) (number? (caddr E))) (list '* (caddr E) (list '* (list '^ (cadr E) (- (caddr E) 1)) (deriv (cadr E)))))
    (else (list 'deriv E))
  )
)

;simp E simplifys a single binary expression E

(define (simp E)
  (cond
    ((number? E) E)
    ((symbol? E) E)
    (else
      (let ((opr (car E));opr is the operator of expression E
           (a (cadr E))
           (b (caddr E)))
        (cond
          ((eq? opr '+) (cond
                          ((and (number? a) (number? b)) (+ a b))
                          ((equal? b 0) a)  ;x + 0 = x
                          ((equal? a 0) b)  ;0 + x = x
                          (else E)
                        )
          )
          ((eq? opr '-) (cond
                          ((and (number? a) (number? b)) (- a b))
                          ((equal? b 0) a)  ;x - 0 = x
                          (else E)
                        )
          )
          ((eq? opr '*) (cond
                          ((and (number? a) (number? b)) (* a b))
                          ((equal? b 0) 0)  ;x * 0 = 0 
                          ((equal? a 0) 0)  ;0 * x = 0
                          ((equal? a 1) b)  ;1 * x = x
                          ((equal? b 1) a)  ;x * 1 = x
                          (else E)
                        )
          )
          ((eq? opr '^) (cond
                          ((and (number? a) (number? b)) (expt a b))
                          ((equal? b 1) a)  ;x^1 = x
                          ((equal? a 1) 1)  ;1^x = 1
                          (else E)
                        )
          )
          ((eq? opr '/) E)
          ((eq? opr 'deriv) E)
        )
      )
    )
  )
)

;simplify E simplifys an expression E

(define (simplify E)
  (cond
    ((number? E) E)
    ((symbol? E) E)
    ((eq? (car E) 'deriv) E)
    (else (let ((a (simplify (cadr E)))
                (b (simplify (caddr E)))
               )
            (simp (list (car E) (simp a) (simp b)))
          )
    )
  )
)

;derivative E returns the derivative of E in a simplified form

(define (derivative E) (simplify (deriv E)))

(derivative '(+ (+ (^ x 2) x) 5))



