---
title: 'chronovise: Measurement-Based Probabilistic Timing Analysis framework'
tags:
- probabilistic real-time
- mbpta
- worst-case execution time
- extreme value theory
authors:
- name: Federico Reghenzani
  orcid: 0000-0002-1888-9579
  affiliation: 1
- name: Giuseppe Massari
  orcid: 0000-0002-2302-4297
  affiliation: 1
- name: William Fornaciari
  orcid: 0000-0001-8294-730X
  affiliation: 1

affiliations:
- name: Dipartimento di Elettronica, Informazione e Bioingegneria, Politecnico di Milano
  index: 1
date: 13 April 2018
bibliography: paper.bib
---

# Summary
The rapid advance of computer architectures towards more powerful, but also
more sophisticated and complex platforms, has the side effect of making the
timing analysis of applications a challenging task [@cullmann2010predictability].
The increasing demand of computational power
in cyber-physical systems (CPS) is getting hard to fulfill, if we consider
typical real-time constrained applications. Time constraints in CPS are often
mandatory requirements, i.e. the timing requirements must be satisfied in any
condition because of the mission-critical system purpose. The satisfaction of
these constraints is traditionally demonstrated using well-known *static
analyses* providing the **Worst-Case Execution Time (WCET)**. However, the
increasing complexity of computer architectures -- such as multi-core,
multi-level caches, complex pipelines, etc. [@berg2004requirements] --  makes
these analyses computationally unaffordable or too pessimistic. The problem
grows when dealing with Commercial-Off-The-Shelf (COTS) hardware
[@dasari2013identifying] and complex operating systems [@reghenzani2017mixed].

*Probabilistic hard real-time* has been proposed as a possible solution to
address this complexity increase [@bernat2002wcet]. In particular, the
**Measurement-Based Probabilistic Time Analysis (MBPTA)** is a probabilistic
real-time branch focused on the estimation of the WCET, directly from the
observed execution times of real-time tasks.  The task execution time is
measured across its input domain and the WCET is provided as a so-called
probabilistic-WCET (pWCET), i.e. a WCET with a probability of observing higher
execution times.  The statistical **Extreme Value Theory (EVT)**, typically
used in natural disaster risk evaluation, is the basis for pWCET estimation.
However, to obtain a safe pWCET estimation, the execution time traces must
fulfill the requirements of EVT that can be checked running appropriate testing
procedures [@santinelli2017revising].

The *chronovise* framework is an open-source software aiming at standardizing
the flow of MBPTA process, integrating both estimation and testing phases. The
few previous works in literature are [@5591317] and [@Lesage2015], for which
source code is not available.  Moreover, both works include a limited set of
features, other than poor maturity level due to the missing integration of the
most recent scientific contributions.  Our work aim at filling the absence of
a stable software with a well-defined EVT execution flow.  The proposed
framework supports both Block-Maxima (BM) and Peak-over-Threshold (PoT) EVT
approaches; the current available methods to estimate the extreme
distribution. The output distribution respectively assumes the Generalized
Extreme Value (GEV) and the Generalized Pareto Distribution (GPD) form. A
couple of estimators (MLE and PWM) are already included, as well as some
statistical tests: Kolmogorov-Smirnov [@massey1951kolmogorov] and (Modified)
Anderson-Darling [@sinclair1990modified]. Finally, the implementation of an
overall results confidence estimation procedure is also available.  The API
provided allows users to specify or to implement new input generators and
input representativity tests.

The software *chronovise* is in fact presented as a flexible and
extensible framework, deployed as a static C++ library. The selection of C++
language enables the easy implementation of hardware-in-the-loop analyses.
The underlying idea of *chronovise* is to provide a common framework for both
researchers and users.  Even if EVT is a well-known statistical theory, it is
continuously evolving and it is still a hot topic in mathematical environment.
The application of EVT in real-time computing is immature and it still
requires several theoretical advances. This has led us to implement this
software: enabling the exploitation of an already implemented EVT process, in
order to perform experiments of new theories and methods, without the need to
reimplement algorithms from scratch. With our framework we want to create a
common *software-base*, that would increase both the replicability of the
experiments and the reliability of the results, which are common issues in
research.  On the other hands, pure users -- i.e. engineers that use the
already available algorithms to estimate the pWCET -- can just implement the
measurement part and use the framework without modifying it.

# References
