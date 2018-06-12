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
more complex platforms, has the side effect of making the
timing analysis of applications a challenging task [@cullmann2010predictability].
The increasing demand of computational power
in cyber-physical systems (CPS) is getting hard to fulfill, if we consider
typical real-time constrained applications. Time constraints in CPS are often
mandatory requirements, i.e. they must be satisfied in any
condition because of the mission-critical system purpose. The satisfaction of
these constraints is traditionally demonstrated using well-established *static
analyses*, providing the **Worst-Case Execution Time (WCET)** [@wilhelm2008the].
However, the increasing complexity of computing architectures -- such as multi-core,
multi-level caches, complex pipelines, etc. [@berg2004requirements] --  makes
these analyses computationally unaffordable or carrying out too pessimistic
approximations.
The problem grows when dealing with Commercial-Off-The-Shelf (COTS) hardware
[@dasari2013identifying] and complex operating systems [@reghenzani2017mixed].

Probabilistic approaches for hard real-time systems have been proposed as a
possible solution to address this complexity increase [@bernat2002wcet]. In
particular, the **Measurement-Based Probabilistic Time Analysis (MBPTA)**
[@grosjean2012measurement] is a probabilistic analysis branch for real-time
systems to estimate the WCET directly from the observed execution times of
real-time tasks.
The time samples are collected across the application input domain and the WCET
is provided in probablistic terms, the *probabilistic-WCET (pWCET)*, i.e. a WCET with a
probability of observing higher execution times. The statistical theory at
the basis of the WCET estimation is the **Extreme Value Theory (EVT)**
[@castillo2005extreme] [@de2007extreme], typically used in natural disaster
risk evaluation,
However, to obtain a safe pWCET estimation,
the execution time traces must fulfill certain requirements. In particular,
MBPTA requires the time measurements to be [@kosmidis2017enabling]: (1)
independent and identically distributed, (2) representative of all worst-case
latencies. The first requirement comes from the EVT, it can be checked with
suitable statistical tests and can be relaxed under some circumstances
[@santinelli2017revising], while the latter is relative to the
input representativity and to the system (hardware/software) properties.
Both requirements are necessary to obtain a safe, i.e. non-underestimated,
pWCET.

The *chronovise* framework is an open-source software aiming at standardizing
the flow of MBPTA process, integrating both estimation and testing phases. The
few existing software presented in literature [@5591317] [@Lesage2015] lack of
source code availability. Moreover, both works include a limited
set of features, other than poor maturity level due to the missing integration
of the most recent scientific contributions. Another software is available as
open-source [@abella_jaume_2017_1065776], but specialized for a variant of
classical MBPTA analysis called MBPTA-CV [@abella2017measurement].
Our work aimis at filling the absence of
a stable software with a well-defined EVT execution flow.  The proposed
framework supports both Block-Maxima (BM), Peak-over-Threshold (PoT) and
MBPTA-CV EVT approaches; the current available methods to estimate the extreme
distribution. The output distribution respectively assumes the Generalized
Extreme Value (GEV) and the Generalized Pareto Distribution (GPD) form. Three
estimators, Maximum Likelihood Estimator (MLE) [@bucher2017onthe],
Generalized-MLE (GMLE) [@martins2000generalized],
Probability Weighted Moment (PWM, called also L-moments)
[@hosking1987thegeneralized], are already
included, as well as some statistical tests: Kolmogorov-Smirnov
[@massey1951kolmogorov] and (Modified) Anderson-Darling [@sinclair1990modified].
Finally, the implementation of an overall results confidence estimation procedure
is also available.  The API provided allows users to specify or to implement
new input generators and input representativity tests.

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
research. On the other hand, end-users -- i.e. engineers that use the
already available algorithms to estimate the pWCET -- can just implement the
measurement part and use the framework without introducing further changes.

# References
