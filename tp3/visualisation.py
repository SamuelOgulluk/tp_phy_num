"""
Visualisation des résultats TP3 - Packing de cercles
"""
import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.patches import Circle, Rectangle

# Configuration globale
plt.rcParams['figure.figsize'] = (10, 6)
plt.rcParams['font.size'] = 11
plt.rcParams['lines.linewidth'] = 1.5
plt.rcParams['lines.markersize'] = 5

FIG_DIR = "figures"
RES_DIR = "resultats"
L = 20.0

os.makedirs(FIG_DIR, exist_ok=True)

def q6():
    """Q6: Influence de la température"""
    try:
        data = np.loadtxt(os.path.join(RES_DIR, "q6_q8_temperature.res"))
        T, eta = data[:, 0], data[:, 1]
        
        plt.figure()
        plt.plot(T, eta, 'o-', color='crimson', markersize=6)
        plt.xlabel('Température ($T$)')
        plt.ylabel(r'Fraction de surface ($\eta$)')
        plt.title('Q8: Influence de la Température')
        plt.grid(True, alpha=0.3)
        plt.tight_layout()
        plt.savefig(os.path.join(FIG_DIR, "Q8_Temperature.pdf"), dpi=150, bbox_inches='tight')
        plt.close()
    except Exception as e:
        print(f"Erreur Q6: {e}")

def q7():
    """Q7: Configurations à différentes températures"""
    try:
        temperatures = [0, 1, 2, 5, 10]
        fig, axes = plt.subplots(2, 3, figsize=(15, 10))
        axes = axes.flatten()
        
        for idx, T in enumerate(temperatures):
            ax = axes[idx]
            try:
                data = np.loadtxt(os.path.join(RES_DIR, f"q6_q8_config_T{T}.res"))
                if data.ndim == 1:
                    data = data.reshape(1, -1)
                x, y, R_data = data[:, 0], data[:, 1], data[:, 2]
                
                ax.add_patch(Rectangle((0, 0), L, L, fill=False, edgecolor='black', linewidth=2))
                for i in range(len(x)):
                    ax.add_patch(Circle((x[i], y[i]), R_data[i], fill=True, alpha=0.6, 
                                       edgecolor='blue', facecolor='lightblue', linewidth=0.5))
                for i in range(int(L) + 1):
                    ax.axhline(i, color='red', linewidth=0.3, alpha=0.3, linestyle='--')
                    ax.axvline(i, color='red', linewidth=0.3, alpha=0.3, linestyle='--')
                
                ax.set_xlim(-0.5, L + 0.5)
                ax.set_ylim(-0.5, L + 0.5)
                ax.set_aspect('equal')
                ax.set_title(f'T = {T} (N = {len(x)})', fontweight='bold')
                ax.grid(True, alpha=0.2)
            except:
                ax.text(0.5, 0.5, f'T = {T}\nmanquant', ha='center', va='center', 
                       transform=ax.transAxes)
        
        fig.delaxes(axes[5])
        plt.suptitle('Q7: Configurations à différentes températures', fontsize=14, fontweight='bold')
        plt.tight_layout()
        plt.savefig(os.path.join(FIG_DIR, "Q7_Configurations_Temperature.pdf"), dpi=150, bbox_inches='tight')
        plt.close()
    except Exception as e:
        print(f"Erreur Q7: {e}")
    
def q10():
    """Q10: Convergence MAX_TRIES (1000-32000)"""
    try:
        data = np.loadtxt(os.path.join(RES_DIR, "q10_q11_maxtries.res"))
        max_tries, eta_mean = data[:, 0], data[:, 1]
        eta_std = data[:, 2] if data.shape[1] >= 3 else np.zeros_like(eta_mean)
        mask = max_tries <= 32000
        
        fig, ax = plt.subplots(figsize=(10, 6))
        ax.errorbar(max_tries[mask], eta_mean[mask], yerr=eta_std[mask],
                   fmt='s-', color='green', markersize=8, linewidth=2,
                   capsize=5, capthick=2, label=r'$\eta$ moyenne $\pm$ écart-type')
        ax.set_xscale('log')
        ax.set_xlabel('MAX_TRIES (log)', fontsize=12, fontweight='bold')
        ax.set_ylabel(r'Fraction $\eta$', fontsize=12, fontweight='bold')
        ax.set_title('Q10: Convergence (1000 → 32000)', fontsize=13, fontweight='bold')
        ax.grid(True, alpha=0.3, which='both')
        ax.legend()
        plt.tight_layout()
        plt.savefig(os.path.join(FIG_DIR, "Q10_Convergence.pdf"), dpi=150, bbox_inches='tight')
        plt.close()
    except Exception as e:
        print(f"Erreur Q10: {e}")

def q11():
    """Q11: Convergence MAX_TRIES complète (jusqu'à 512000)"""
    try:
        data = np.loadtxt(os.path.join(RES_DIR, "q10_q11_maxtries.res"))
        max_tries, eta_mean = data[:, 0], data[:, 1]
        eta_std = data[:, 2] if data.shape[1] >= 3 else np.zeros_like(eta_mean)
        mask_q10, mask_q11 = max_tries <= 32000, max_tries > 32000
        
        fig, ax = plt.subplots(figsize=(12, 6))
        ax.errorbar(max_tries[mask_q10], eta_mean[mask_q10], yerr=eta_std[mask_q10],
                   fmt='s-', color='green', markersize=8, linewidth=2,
                   capsize=5, capthick=2, label='Q10 (1000-32000)')
        if np.any(mask_q11):
            ax.errorbar(max_tries[mask_q11], eta_mean[mask_q11], yerr=eta_std[mask_q11],
                       fmt='o-', color='darkblue', markersize=8, linewidth=2,
                       capsize=5, capthick=2, label='Q11 (64000-512000)')
        ax.set_xscale('log')
        ax.set_xlabel('MAX_TRIES (log)', fontsize=12, fontweight='bold')
        ax.set_ylabel(r'Fraction $\eta$', fontsize=12, fontweight='bold')
        ax.set_title('Q11: Convergence complète (1000 → 512000)', fontsize=13, fontweight='bold')
        ax.grid(True, alpha=0.3, which='both')
        ax.legend(loc='lower right')
        plt.tight_layout()
        plt.savefig(os.path.join(FIG_DIR, "Q11_Convergence_Full.pdf"), dpi=150, bbox_inches='tight')
        plt.close()
    except Exception as e:
        print(f"Erreur Q11: {e}")


def main():
    """Génère tous les graphiques du TP3"""
    for func in [ q6, q7, q10, q11]:
        try:
            func()
        except Exception as e:
            print(f"Erreur lors de l'exécution de {func.__name__}: {e}")

if __name__ == "__main__":
    main()