# Dynamic Social Impact Theory (DSIT) C++ Simulation

This repository contains a C++ program that simulates individual-level communication and social organization. It is based on Dynamic Social Impact Theory (Latané, 1996), which models how culture is created through communication. For an in-depth exploration of these methods and findings, please read the .docx file located in the main directory. 

## 🧠 Project Overview
The program tests whether individual influence processes iteratively lead to global self-organization, such as spatial clustering and attribute correlation. 

* **The Environment:** 400 individuals are simulated within a 20x20 matrix.
* **The Data Structure:** The environment is built using a conventional graph structure $G = (V,E)$ implemented via dynamic arrays (vectors). 
* **The Nodes:** Each vertex represents an individual (struct) containing a continuous attitude measurement, a 2D spatial location, and an adjacency vector.
* **The Edges:** The graph is undirected and bidirectional. Edge weights simulate the physical distance between individuals.

## 🧮 Core Mathematical Models
Social influence is programmed as a multiplicative function of an individual's strength and immediacy, and inversely proportional to their distance. 

**1. Social Influence Calculation (Delta)**
For a single act of social impact of Person X on Person Y, the change ($\Delta$) is calculated based on initial attitudes ($Att$), Stable Strength ($SS$), and Distance ($Dist$):

$$\Delta = \frac{(AttX_0 - AttY_0) \cdot SS_X}{Dist_{X,Y}} \cdot SS_Y$$ 

**2. Attitude Update**
The resulting delta is used to update the attitude of the influenced individual, moderated by a constant ($C$) representing the overall degree of communication in the simulated culture:

$$AttY_i = AttY_{i-1} - \frac{\Delta}{C}$$

**3. Variance Over Time**
Due to the functional limitations of the C++ `double` data type (15 decimal places), the variance ($f(i)$) approaches zero as iterations approach infinity:

$$\lim_{i \to \infty} f(i) = 0$$ 

## 📊 Key Findings & Emergent Properties
* **Spatial Clustering:** The simulation successfully produced global self-organization; people became more similar to their neighbors, leading to visual spatial clustering. 
* **Minority Protection:** Minority attitudes typically declined in overall numbers but were able to survive to the extent that they were protected by these clusters.
* **The Impact of Strength:** When stable strength ($SS$) was held equal, overall attitude valence was conserved. However, when $SS$ was introduced as a randomized variable, conservation broke down, allowing single high-strength individuals to drastically alter the global consensus. 

## 📚 References
* Latané, B. (1996). Dynamic Social Impact: The Creation of Culture by Communication. *Journal of Communication*, 46(4), 13–25.

  Disclaimer: This README was constructed with the help of the Gemini LLM, based on my own paper summary. 
