---
title: 'chronovise: Measurement-Based Probabilistic Timing Analysis'
tags:
- probabilistic real-time
- mbpta
- wcet
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
date: 11 April 2018
bibliography: paper.bib
---

# Summary
The rapid advance of computer architectures towards more powerful but also more sophisticated and
complex platforms has the side effect of making the timing analysis of applications challenging 
[@cullmann2010predictability].
The increasing demand of computational power needed by applications is getting hard to fulfill for
cyber-physical systems (CPS) having real-time constraints. Real-time constraints for CPS are
frequently compulsory, i.e. the timing constraints must be satisfied in any condition because of the
mission-critical system purpose. The satisfaction of these
constraints are traditionally performed using well-known *static analyses* that provide a
**Worst-Case Execution Time (WCET)**. However, the increasing
complexity of computer architectures -- such as multi-core, multi-level caches, complex pipelines,
etc. [@berg2004requirements] --  makes these analyses computationally unaffordable or too
pessimistic. The problem grows when dealing with Commercial-Off-The-Shelf (COTS) hardware
[@dasari2013identifying] and complex operating systems [@reghenzani2017mixed].

Probabilistic hard real-time has been proposed as a possible solution to architecture
complexity increasing [@bernat2002wcet]. In particular, the **Measurement-Based Probabilistic
Time Analysis (MBPTA)** is the branch of probabilistic real-time that estimates the WCET
directly from the observed execution times of the real-time task.
The task execution time is measured across its input
domain and the WCET is provided as a so-called probabilistic-WCET (pWCET), i.e. a WCET with a
probability of observing higher execution times.
The statistical **Extreme Value Theory (EVT)**, typically used in natural disaster risk evaluation,
is the basis for pWCET estimation.

The *chronovise* framework is an open-source software aiming at standardizing the flow of EVT
process, integrating both estimation phases and testing phases. The only previous works in literature
are [@5591317] and [@Lesage2015], however the unavailability of source code, the limited features
and the immaturity given the absence of subsequent works are the main reasons of our work, that wants
to fill the absence of a stable software with a well-defined EVT execution flow. The framework
supports both Block-Maxima (BM) and Peak-over-Threshold (PoT) EVT approaches, the current available
methods to estimate the extreme distribution. The output distribution respectively
assumes the Generalized Extreme Value (GEV) and the Generalized Pareto Distribution (GPD) form. A
couple of already implemented estimators (MLE and PWM) is available and also a couple of statistical
tests: Kolmogorov-Smirnov [@massey1951kolmogorov] and (Modified) Anderson-Darling
[@sinclair1990modified]. The API to provide an input generator and input representativity tests is
also available to the user. Finally, an overall results confidence estimation computation is
provided.

Instead of providing a read-to-use and fixed tool, *chronovise* is proposed as a flexible and
extensible framework deployed as a static C++ library. The selection of C++ language enables the
easy implementation of hardware-in-the-loop analyses.
The behind idea of *chronovise* is to provide a common framework for both researchers and users.
Even if EVT is a well-known statistical theory, it is continuously evolving and still a hot topic
in mathematical environment. The application of EVT in real-time field is immature and it
still requires several theoretical advances. This is that leads us to implement this software:
enabling the exploitation of an already implemented EVT process in order to perform experiments of
new theories and methods, without the need to reimplement all the algorithms from scratch. Our
framework wants to create a common *software-base*, that would increase both the replicability and
reliability of the results, common nowadays problems in computer science research.
On the other hands, pure users -- i.e. engineers that use the already 
available algorithms to estimate the pWCET -- can just implement the measurement part and use the
framework without modifying it.

# References
