A brief introduction to MBPTA
=============================
The **Measurement-Based Probabilistic Timing Analysis (MBPTA)** is a technique to estimate the **Worst-Case
**Execution Time (WCET)** of a given application in the context of probabilistic real-time computing.
The WCET is derived
in probablistic sense (_pWCET_), i.e. the execution time is upper-bounded by a WCET value with a certain
confidence.
The hard real-time guarantee of "do not miss deadlines" is then provided with a probability of failure.

The MBPTA technique relies on observations of execution time of a given task. The execution times should
be used to estimate a distribution using the **Extreme Value Theory (EVT)**. MBPTA can work using two different
statistical results: **Block-Maxima (BM)** or **Peak-over-Threshold (PoT)**.
In the first case the timing measurements
are divided into buckets of equal size, and the maximums of these buckets are fed into an EVT estimator to
obtain the statistical distribution of extremes. In the latter case, PoT, the timing measurements are
filtered via a fixed threshold and the remaining timing measurements are used to estimate the distribution.
In BM approach the distribution follows a **Generalized Extreme Value** distribution (GEV). Instead, in the
PoT approach the distribution is a **Generalized Pareto Distribution** (GPD). These distributions are then
used to derive the pWCET.

However, MBPTA and in general EVT has some property requirements, especially of the input data, that must
be fulfilled in order to obtain estimations that can be considered "safe". The most important one is the
i.i.d. condition* of the time measurements in input.

For this reason, a series of
statistical tests must be performed before and after the EVT estimation to obtain a result that can be
considered *safe*. The exact confidence of the result is not trivial to calculate and it's still an open
problem in research.

The following steps are required to run an EVT estimation:
 - Generate a valid input dataset that covers all execution time scenarios
 - Verify that the input data satisfy the EVT conditions
 - Apply BM or PoT to the input data
 - Estimate the Extreme-Value distribution from the BM or PoT output
 - Compute the pWCET

The goal of chronovise framework is to provide these steps in an algorithmic view, leaving the research
to just implement the essential methods.

* This condition can be actually relaxed with other less strict conditions, but this is outside the
  scope of this documentation.