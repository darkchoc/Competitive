SWE ML Takehome Test
Overview

At Arena, we expect Software Engineers to work with ML Scientists to build production-grade systems that incorporate state-of-the-art ML technologies. While expertise in ML is not a prerequisite, we value candidates with a strong interest in learning and writing high-quality ML code.

Goal

In this exercise, you will build a rudimentary Entity Resolution (ER) pipeline capable of resolving retailer entities found in the dataset arena_ml__retailers.csv. Identical retailer entities should be linked together using a technique called Hierarchical Agglomerative Clustering (HAC).

The assignment should take around 2 hours, however the coderpad link will be open for 4 hours. Feel free to use more time, if necessary. We realize that people learn, read, and experiment at varying speeds. Please email swe-coding-test@arena-ai.com to let us know you have completed the test.

A good solution will demonstrate

Clean code
Well thought out design
Documentation
Ability to reason with ML first principles
Pipeline Requirements

Your mission is to build a pipeline capable of resolving retailer entities found in the supplied dataset on coderpad. At minimum, your pipeline should contain the below steps. Feel free to add additional functionality as you see fit.

Pre-process your data. Use the supplied file called arena_ml__retailers.csv. The how and what to pre-process are left to you. The dataset can be found in the Files section on the coderpad test.

Generate a ground truth for the dataset. In supervised ML, the ground truth is something we definitively know to be true.

Use the retailer_nm column to programmatically generate the ground truth. Records should be saved to a column called ground_truth_label. For example
$ cat sample_dataset.csv

ground_truth_label,retailer_nm,retailer_nm_modified
0,Joe’s Pizza,Joe’s3821 PiZzzA
0,Joe’s Pizza,83ddjJoe’s Pizza
1,Al’s Store,aaaL’s store
0,Joe’s Pizza,J03's Pizzaeria
1,Al’s Store,AL’S STORE
Entity Resolution

Implement hierarchical agglomerative clustering from scratch. At minimum, your implementation needs to use the column retailer_nm_modified. You are free to incorporate additional attributes to improve accuracy as you see fit, however do not include the column retailer_nm. Linkage, scoring, thresholds, etc are left up to you.
You are required to implement hierarchical agglomerative clustering from scratch and on your own. No 3rd party libraries can be used for clustering. For example, a solution using scikit-learn for clustering will not be reviewed. You are free to study and read about how the algorithm works. The goal of this step is to understand how you grok first principles.
You are allowed to use 3rd party libraries for calculating the score.
Post-process

Measure the accuracy of your solution. Generate a confusion matrix to calculate the precision and recall for each predicted “class”. Use the ground_truth_label that was generated in an earlier step.
Persist data generated in the pipeline to a CSV file called pipeline_output.csv. The CSV header needs to contain all of the record values and columns from arena_ml__retailer.csv plus the columns below
cluster_id
ground_truth_label
precision_for_cluster_id
recall_for_cluster_id
$ cat pipeline_output.csv

cluster_id,ground_truth_label,precision_for_cluster_id,recall_for_cluster_id,store_record_id,retailer_id,retailer_nm,store_id,store_address_1,store_address_2,store_city,store_state,store_zip_code,store_county,vpid,retailer_nm_modified
Instructions

The solution is to be implemented in Python.
Please do not share this document or code with anyone else.
To access the file arena_ml__retailers.csv click “Files” in the top right menu bar next to the instructions.
You can install additional python packages using the coderpad shell in the bottom right hand corner of coderpad. Make sure to also update requirements.txt. To access the coderpad shell, click “Program Output” in the top right menu bar next to the instructions.
Certain tools are forbidden from being used. Please do not use the tools listed below. For the purpose of this exercise, we want to understand how you solve problems coming from first principles. This is mostly an open book test - you are free to read about entity resolution, hierarchical agglomerative clustering algorithm, distance calculation, creating a confusion matrix, etc.
LLMs must not be used, in any capacity, eg code generation or even as guidance.
3rd party libraries must not be used for implementing the hierarchical agglomerative clustering algorithm.
You are free to use 3rd party libraries such as numpy, pandas, etc.
Please do all of your work inside coderpad (i.e. do not copy/paste the starter code out into your own IDE to work on). We will not review any work done outside of the pad.
Once you have completed and submitted the assessment, please email us at swe-coding-test@arena-ai.com to let us know you’ve finished!