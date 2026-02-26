"""
Visualisation des résultats TP4 - Équation de Schrödinger 1D
"""
import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Configuration globale
plt.rcParams['figure.figsize'] = (10, 6)
plt.rcParams['font.size'] = 11
plt.rcParams['lines.linewidth'] = 1.5
plt.rcParams['lines.markersize'] = 5

FIG_DIR = "figures"
RES_DIR = "resultats"

os.makedirs(FIG_DIR, exist_ok=True)

def question_1_2_potentials():
    try:
        data = np.loadtxt(os.path.join(RES_DIR, "q1_q2_potentials.res"))
        x = data[:, 0]
        plt.figure()
        plt.plot(x, data[:, 1], label="Puits Carré Infini")
        plt.plot(x, data[:, 2], label="Oscillateur Harmonique")
        plt.plot(x, data[:, 3], label="Double Puits")
        plt.title("Comparaison des Potentiels")
        plt.xlabel("Position $x$")
        plt.ylabel("Potentiel $V(x)$")
        plt.legend()
        plt.grid(True, alpha=0.3)
        plt.ylim(-5, 10)
        plt.savefig(os.path.join(FIG_DIR, "Q1_Q2_Potentiels.pdf"), dpi=150, bbox_inches='tight')
        plt.close()
    except: pass

def question_6_7_puits_infini():
    try:
        data_energies = np.loadtxt(os.path.join(RES_DIR, "q6_puits_energies.res"))
        energies_num, energies_theo = data_energies[:, 0], data_energies[:, 1]
        data_ondes = np.loadtxt(os.path.join(RES_DIR, "q6_puits_ondes.res"))
        x = data_ondes[:, 0]
        p_indices = np.arange(len(energies_num))
        
        plt.figure(figsize=(12, 5))
        plt.subplot(1, 2, 1)
        plt.plot(p_indices, energies_num, 'bo', label="Numérique", markersize=5)
        plt.plot(p_indices, energies_theo, 'r-', label="Théorique", linewidth=2)
        plt.xlabel("Indice p")
        plt.ylabel("Énergie")
        plt.title("Énergies")
        plt.legend()
        plt.grid(True, alpha=0.3)
        
        plt.subplot(1, 2, 2)
        erreur = np.abs(energies_num - energies_theo) / energies_theo * 100
        plt.semilogy(p_indices, erreur, 'go-', markersize=4)
        plt.xlabel("Indice p")
        plt.ylabel("Erreur relative (%)")
        plt.title("Précision")
        plt.grid(True, alpha=0.3)
        plt.suptitle("Q6 : Puits Infini")
        plt.tight_layout()
        plt.savefig(os.path.join(FIG_DIR, "Q6_Puits_Energies.pdf"), dpi=150, bbox_inches='tight')
        plt.close()

        plt.figure(figsize=(10, 8))
        scale, L = 3.0, 5.0
        colors = ['blue', 'red', 'green']
        for p in range(3):
            psi = data_ondes[:, p+1]
            densite = (psi ** 2) * scale + energies_num[p]
            plt.plot(x, densite, color=colors[p], linewidth=2, label=f"$p={p}$, $E={energies_num[p]:.3f}$")
            plt.axhline(energies_num[p], color=colors[p], linestyle=':', alpha=0.4)
        plt.axvline(-L/2, color='black', linestyle='--', linewidth=2, alpha=0.6)
        plt.axvline(L/2, color='black', linestyle='--', linewidth=2, alpha=0.6)
        plt.title(r"Q7 : Fonctions d'onde")
        plt.xlabel("Position $x$")
        plt.ylabel(r"$|\psi|^2 + E$")
        plt.legend()
        plt.grid(True, alpha=0.3)
        plt.xlim(-L/2 - 0.3, L/2 + 0.3)
        plt.tight_layout()
        plt.savefig(os.path.join(FIG_DIR, "Q7_Puits_Ondes.pdf"), dpi=150, bbox_inches='tight')
        plt.close()
    except: pass

def question_9_10_harmonique_energies():
    configs = [("n100_L5", "L=5", 'blue'), ("n100_L20", "L=20", 'red')]
    fig = plt.figure(figsize=(15, 5))
    ax1, ax2, ax3 = plt.subplot(1, 3, 1), plt.subplot(1, 3, 2), plt.subplot(1, 3, 3)
    
    for suffix, label, color in configs:
        filename = os.path.join(RES_DIR, f"q9_harm_energies_{suffix}.res")
        if os.path.exists(filename):
            data = np.loadtxt(filename)
            energies_num, energies_theo = data[:, 0], data[:, 1]
            p_indices = np.arange(len(energies_num))
            erreur = np.abs(energies_num - energies_theo) / energies_theo * 100
            
            ax1.plot(p_indices, energies_num, 'o-', color=color, label=label, markersize=3)
            ax2.semilogy(p_indices, erreur, 'o-', color=color, label=label, markersize=3)
            ax3.plot(p_indices[:10], energies_num[:10], 'o-', color=color, label=label, markersize=5)
            if suffix == "n100_L5":
                ax3.plot(p_indices[:10], energies_theo[:10], 'k--', label="Théo", linewidth=2)
    
    for ax in [ax1, ax2, ax3]:
        ax.set_xlabel("Indice p")
        ax.legend()
        ax.grid(True, alpha=0.3)
    ax1.set_ylabel("Énergie")
    ax1.set_title("Énergies numériques")
    ax2.set_ylabel("Erreur (%)")
    ax2.set_title("Précision")
    ax3.set_ylabel("Énergie")
    ax3.set_title("Zoom 10 premiers")
    plt.suptitle("Q9 & Q10 : Oscillateur Harmonique")
    plt.tight_layout()
    plt.savefig(os.path.join(FIG_DIR, "Q9_Q10_Harmonique_Comparison.pdf"), dpi=150, bbox_inches='tight')
    plt.close()

def question_11_harmonique_ondes():
    suffix = "n100_L5"
    files = [f"q9_harm_ondes_{suffix}.res", f"q9_harm_energies_{suffix}.res", f"q9_harm_pot_{suffix}.res"]
    if not all(os.path.exists(os.path.join(RES_DIR, f)) for f in files):
        return
    
    try:
        data_ondes = np.loadtxt(os.path.join(RES_DIR, files[0]))
        energies_num = np.loadtxt(os.path.join(RES_DIR, files[1]))[:, 0]
        data_pot = np.loadtxt(os.path.join(RES_DIR, files[2]))
        x, V = data_ondes[:, 0], data_pot[:, 1]
        
        plt.figure(figsize=(10, 8))
        plt.plot(x, V, 'k--', linewidth=2, label="Potentiel", alpha=0.6)
        scale, colors = 0.8, ['blue', 'red', 'green']
        for p in range(3):
            psi = data_ondes[:, p+1]
            densite = (psi ** 2) * scale + energies_num[p]
            plt.plot(x, densite, color=colors[p], linewidth=2, label=f"$p={p}$, $E={energies_num[p]:.3f}$")
            plt.axhline(energies_num[p], color=colors[p], linestyle=':', alpha=0.4)
        plt.title(r"Q11 : Oscillateur Harmonique")
        plt.xlabel("Position $x$")
        plt.ylabel(r"$|\psi|^2 + E$")
        plt.ylim(0, 6)
        plt.xlim(-3, 3)
        plt.legend()
        plt.grid(True, alpha=0.3)
        plt.tight_layout()
        plt.savefig(os.path.join(FIG_DIR, "Q11_Harmonique_Ondes.pdf"), dpi=150, bbox_inches='tight')
        plt.close()
    except: pass

def plot_double_puits(suffix, title, filename):
    files = [f"q12_double_ondes{suffix}.res", f"q12_double_pot{suffix}.res", f"q12_double_energies{suffix}.res"]
    if not all(os.path.exists(os.path.join(RES_DIR, f)) for f in files):
        return
    
    try:
        data_ondes = np.loadtxt(os.path.join(RES_DIR, files[0]))
        data_pot = np.loadtxt(os.path.join(RES_DIR, files[1]))
        energies = np.loadtxt(os.path.join(RES_DIR, files[2]))
        x, V = data_ondes[:, 0], data_pot[:, 1]
        
        fig = plt.figure(figsize=(14, 10))
        colors = ['blue', 'red', 'green', 'purple']
        scale = 5.0 if "deep" in suffix else 0.3
        
        ax1 = plt.subplot(2, 1, 1)
        ax1.plot(x, V, 'k-', linewidth=3, label="Potentiel", alpha=0.7)
        for p in range(4):
            psi = data_ondes[:, p+1]
            densite = (psi ** 2) * scale + energies[p]
            ax1.plot(x, densite, color=colors[p], linewidth=2, label=f"$\\psi_{p}$, $E={energies[p]:.2f}$")
            ax1.axhline(energies[p], color=colors[p], linestyle=':', alpha=0.3)
        ax1.set_xlabel("Position $x$")
        ax1.set_ylabel(r"$|\psi|^2 + E$ et $V$")
        ax1.set_title(title)
        ax1.legend(ncol=2, fontsize=9)
        ax1.grid(True, alpha=0.3)
        ax1.set_xlim(-3, 3)
        V_zoom = V[np.abs(x) < 3]
        y_min = np.percentile(V_zoom, 1) if "deep" in suffix else min(V_zoom)
        y_max = max(energies[3] + scale*1.5, -1000 if "deep" in suffix else 8)
        ax1.set_ylim(y_min if "deep" in suffix else y_min*1.1, y_max)
        
        ax2 = plt.subplot(2, 1, 2)
        for p in range(4):
            psi = data_ondes[:, p+1]
            ax2.plot(x, psi, color=colors[p], linewidth=2, label=f"$\\psi_{p}$")
        ax2.axhline(0, color='k', linestyle='-', linewidth=1, alpha=0.5)
        ax2.axvline(0, color='k', linestyle='--', linewidth=1, alpha=0.3)
        ax2.set_xlabel("Position $x$")
        ax2.set_ylabel(r"$\psi(x)$")
        ax2.set_title("Fonctions d'onde")
        ax2.legend(fontsize=10)
        ax2.grid(True, alpha=0.3)
        ax2.set_xlim(-3, 3)
        y_max_psi = max([np.max(np.abs(data_ondes[:, p+1][np.abs(x) < 3])) for p in range(4)])
        ax2.set_ylim(-y_max_psi*1.2, y_max_psi*1.2)
        
        plt.tight_layout()
        plt.savefig(os.path.join(FIG_DIR, filename), dpi=150, bbox_inches='tight')
        plt.close()
    except: pass

def question_12_double_puits():
    plot_double_puits("_q12_sym", "Q12 : Double Puits Symétrique", "Q12_Double_Puits.pdf")

def question_13_double_puits_profond():
    plot_double_puits("_q13_deep", "Q13 : Double Puits Profond", "Q13_Double_Puits_Profond.pdf")

def question_14_double_puits_asymetrique():
    plot_double_puits("_q14_asym", "Q14 : Double Puits Asymétrique", "Q14_Double_Puits_Asym.pdf")

def question_12_13_14_comparaison():
    configs = [("_q12_sym", "Sym (a=1)", 'blue'), ("_q13_deep", "Profond (a=400)", 'red'), ("_q14_asym", "Asym (r₃=0)", 'green')]
    fig = plt.figure(figsize=(18, 12))
    
    # Potentiels Q12 vs Q14
    ax1 = plt.subplot(2, 3, 1)
    for suffix, label, color in configs:
        if suffix != "_q13_deep":
            f = os.path.join(RES_DIR, f"q12_double_pot{suffix}.res")
            if os.path.exists(f):
                data = np.loadtxt(f)
                ax1.plot(data[:, 0], data[:, 1], color=color, linewidth=3, label=label)
    ax1.set_xlabel("$x$")
    ax1.set_ylabel("$V(x)$")
    ax1.set_title("Potentiels Q12 vs Q14")
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    ax1.set_xlim(-3, 3)
    ax1.set_ylim(-8, 8)
    
    # Potentiel Q13
    ax2 = plt.subplot(2, 3, 2)
    f13 = os.path.join(RES_DIR, "q12_double_pot_q13_deep.res")
    if os.path.exists(f13):
        data = np.loadtxt(f13)
        x_zoom = data[:, 0]
        V_zoom = data[:, 1]
        ax2.plot(x_zoom, V_zoom, color='red', linewidth=3, label='Profond (a=400)')
        V_in_range = V_zoom[np.abs(x_zoom) < 3]
        V_min = min(V_in_range)
        ax2.set_ylim(V_min * 1.1, 100)
        ax2.axhline(0, color='black', linestyle='--', linewidth=1, alpha=0.5)
    ax2.set_xlabel("$x$")
    ax2.set_ylabel("$V(x)$")
    ax2.set_title("Potentiel Q13 (Puits Profond)")
    ax2.legend()
    ax2.grid(True, alpha=0.3)
    ax2.set_xlim(-3, 3)
    
    # Niveaux d'énergie
    ax3 = plt.subplot(2, 3, 3)
    for i, (suffix, label, color) in enumerate(configs):
        f = os.path.join(RES_DIR, f"q12_double_energies{suffix}.res")
        if os.path.exists(f):
            E = np.loadtxt(f)[:4]
            for j, e in enumerate(E):
                ax3.plot([i-0.4, i+0.4], [e, e], color=color, linewidth=4, alpha=0.8)
                ax3.text(i, e, f'$E_{j}$', ha='center', va='bottom', fontsize=8, fontweight='bold')
    ax3.set_xticks([0, 1, 2])
    ax3.set_xticklabels(['Q12\nSym', 'Q13\nProfond', 'Q14\nAsym'], fontsize=10)
    ax3.set_ylabel("Énergie propre $E_p$", fontsize=11)
    ax3.set_title("Spectres des 4 premiers niveaux", fontweight='bold')
    ax3.grid(True, alpha=0.3, axis='y')
    ax3.set_xlim(-0.6, 2.6)
    
    # États fondamental et excité
    for ax_num, col_idx, state_label in [(4, 1, "Fondamental"), (5, 2, "Excité")]:
        ax = plt.subplot(2, 3, ax_num)
        for suffix, label, color in configs:
            f = os.path.join(RES_DIR, f"q12_double_ondes{suffix}.res")
            if os.path.exists(f):
                data = np.loadtxt(f)
                ax.plot(data[:, 0], data[:, col_idx]**2, color=color, linewidth=3, label=label)
        ax.set_xlabel("$x$")
        ax.set_ylabel(r"$|\psi|^2$")
        ax.set_title(f"État {state_label}")
        ax.legend()
        ax.grid(True, alpha=0.3)
        ax.set_xlim(-3, 3)
    
    # Écart tunnel (splitting E1 - E0)
    ax6 = plt.subplot(2, 3, 6)
    delta_Es, labels, colors_bar = [], [], []
    for suffix, label, color in configs:
        f = os.path.join(RES_DIR, f"q12_double_energies{suffix}.res")
        if os.path.exists(f):
            E = np.loadtxt(f)
            delta_Es.append(E[1] - E[0])
            labels.append(label.split('(')[0])
            colors_bar.append(color)
    
    bars = ax6.bar(range(len(delta_Es)), delta_Es, color=colors_bar, alpha=0.7, edgecolor='black', linewidth=2)
    ax6.set_xticks(range(len(delta_Es)))
    ax6.set_xticklabels(labels, fontsize=10)
    ax6.set_ylabel(r"$\Delta E = E_1 - E_0$", fontsize=11)
    ax6.set_title(r"Splitting tunnel $E_1 - E_0$" + "\n(Effet tunnel entre puits)", fontweight='bold', fontsize=10)
    ax6.set_yscale('log')
    ax6.grid(True, alpha=0.3, axis='y')
    for bar, val in zip(bars, delta_Es):
        ax6.text(bar.get_x() + bar.get_width()/2., bar.get_height()*1.8, f'{val:.2e}', ha='center', va='bottom', fontweight='bold', fontsize=9)
    
    plt.suptitle("Comparaison Q12-Q13-Q14", fontsize=16, fontweight='bold')
    plt.tight_layout()
    plt.savefig(os.path.join(FIG_DIR, "Q12_13_14_Comparaison.pdf"), dpi=300, bbox_inches='tight')
    plt.close()

def question_8_comparaison_psi():
    try:
        data_ondes = np.loadtxt(os.path.join(RES_DIR, "q6_puits_ondes.res"))
        x = data_ondes[:, 0]
        L = 5.0
        
        for p in [1, 55]:
            plt.figure(figsize=(10, 6))
            psi_num = data_ondes[:, p]
            
            # Théorique: sqrt(2/L) * sin(p*pi*(x + L/2)/L)
            psi_theo = np.sqrt(2.0/L) * np.sin(p * np.pi * (x + L/2.0) / L)
            
            if np.sum(psi_num * psi_theo) < 0:
                psi_num = -psi_num
                
            plt.plot(x, psi_theo, 'r-', label=f"Théorique ($p={p}$)", linewidth=2, alpha=0.7)
            plt.plot(x, psi_num, 'b--', label=f"Numérique ($p={p}$)", linewidth=2)
            
            plt.title(f"Comparaison Fonction d'Onde p={p}")
            plt.xlabel("Position x")
            plt.ylabel("$\psi(x)$")
            plt.legend()
            plt.grid(True, alpha=0.3)
            
            if p == 55:
                plt.xlim(-1, 1) 
                plt.title(f"Comparaison Fonction d'Onde p={p} (Zoom central)")
            
            plt.tight_layout()
            plt.savefig(os.path.join(FIG_DIR, f"Q8_Comparaison_p{p}.pdf"), dpi=150, bbox_inches='tight')
            plt.close()
    except Exception as e:
        print(f"Erreur Q8: {e}")

def main():
    """Génère tous les graphiques du TP4"""
    functions = [
        question_1_2_potentials,
        question_6_7_puits_infini,
        question_8_comparaison_psi,
        question_9_10_harmonique_energies,
        question_11_harmonique_ondes,
        question_12_double_puits,
        question_13_double_puits_profond,
        question_14_double_puits_asymetrique,
        question_12_13_14_comparaison
    ]
    for func in functions:
        try:
            func()
        except Exception as e:
            print(f"Erreur lors de l'exécution de {func.__name__}: {e}")


if __name__ == "__main__":
    main()