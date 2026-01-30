# Vitamin-V
This is the COSSIM [1] extension which is developed to simulate complete HPC and/or Cloud applications, supporting both the RISC-V Vector (RVV) and Cryptographic extensions, in a fully distributed manner. 

## The contribution of this work can be summarized in the following points:
- Development of an open-source multi-node integrated simulation framework which can simulate complete RISC-V Systems supporting modern RISC-V extensions.
- An innovative flow to enable the designers to simulate the complete aspects of RISC-V Systems (i.e. CPU and Network Environment) through real applications within one simulation framework.
- An open-source GitHub repository that includes an RVV1.0-enabled HPCG benchmark, dot product and sparse matrix-vector multiplication (SpMV) algorithms, as well as a RISC-V Crypto benchmark for execution on both simulated and physical RISC-V CPUs.
- The integration of VEF traces Framework [2] to analyze communication traffic of MPI-based applications and generate traces that can be used to feed other network simulators.
- A thorough evaluation of the end system based on real-world distributed applications and benchmarks using RISC-V cryptography extensions as well as RVV 1.0.

## Execution
We have created a Virual Machine which we have install everything there. You may download it from [here](https://ihuedu-my.sharepoint.com/:f:/g/personal/ntampouratzis_ihu_gr/IgDeF22T4MgyTratYp_LLbkjAZ-QJm7BV_28bERZRCFfJr8?e=dWtGTD) (It is tested using VMWare 16.1 tools - [download the VM tools for Windows from here](https://ihuedu-my.sharepoint.com/:u:/g/personal/ntampouratzis_ihu_gr/EceCqMJ2-QdOpL3wbKX7bW8BZAuX1MzVrEpsxS9IpzNXJw?e=9HiYY4)). The VM password is <b>1234</b> .

You may see the related video for instructions [MPI-on-COSSIM-multinode](https://ihuedu-my.sharepoint.com/:v:/g/personal/ntampouratzis_ihu_gr/IQAm0LqGLb6bQJsPdnUXOIstASQIEjYtwwNKTkoW47LPYNo). 
Finally, you may see the execution of multi-node Llama Large Language Model [Llama-on-COSSIM-multinode](https://ihuedu-my.sharepoint.com/:v:/g/personal/ntampouratzis_ihu_gr/IQD0hXV6SHr7RIZMQXh8obsdAecNBIodR6W89E8wlcacBrk).


## References
<a id="1">[1]</a> 
N. Tampouratzis, I. Papaefstathiou, A. Nikitakis, A. Brokalakis,
S. Andrianakis, A. Dollas, M. Marcon, and E. Plebani, “A novel,
highly integrated simulator for parallel and distributed systems,”
ACM Trans. Archit. Code Optim., vol. 17, no. 1, Mar. 2020.
Available: https://dl.acm.org/doi/10.1145/3378934

<a id="2">[2]</a> Andújar, F.J., Sánchez de la Rosa, M., Escudero-Sahuquillo, J. et al. Extending the VEF traces framework to model data center network workloads. J Supercomput 79, 814–831 (2023). https://doi.org/10.1007/s11227-022-04692-0
