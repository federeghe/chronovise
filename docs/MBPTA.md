A brief introduction to MBPTA
=============================
The **Measurement-Based Probabilistic Timing Analysis (MBPTA)** is a technique to derive the **Worst-Case
**Execution Time (WCET)** of a given application in the context of probabilistic real-time computing.
The WCET is derived
in probablistic sense (_pWCET_), i.e. the execution time is upper bounded by a WCET value with a certain
confidence.
The hard real-time guarantee of "do not miss deadlines" is provided with a probability of failure.

The MBPTA technique relies on observations of execution time of a given application. The execution times should
be used to estimate a distribution using the **Extreme Value Theory (EVT)**. MBPTA can work using two different
statistical results: **Block-Maxima (BM)** or **Peak-over-Threshold (PoT)**.
In the first case the timing measurements
are divided into buckets of equal size, and the maximums of these buckets are fed into an EVT estimator to
obtain the statistical distribution of extremes. This distribution is then used to derive the pWCET.
In BM approach the distribution follows a **Generalized Extreme Value** distribution (GEV). Instead, in the
PoT approach the distribution is a **Generalized Pareto Distribution** (GPD).

However, MBPTA and in general EVT has some property requirements, especially of the input data, that must
be fulfilled in order to obtain estimations that can be considered "safe". For this reason



