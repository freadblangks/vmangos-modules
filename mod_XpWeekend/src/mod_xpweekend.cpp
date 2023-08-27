#include "ScriptDevMgr.h"
#include "Player.h"
#include "Unit.h"
#include <time.h>

time_t t = time(NULL);
tm* now = localtime(&t);

class xp_weekend : public PlayerScript
{
public:
    xp_weekend() : PlayerScript("mod_xpweeknd") { }

    bool IsWeekend()
    {
        if (now->tm_wday == 5 /*Friday*/ || now->tm_wday == 6 /*Satureday*/ || now->tm_wday == 0/*Sunday*/)
            return true;

        return false;
    }

    void OnLogin(Player* player) override
    {
        ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00DoubleXP Weekend |r");

        if (IsWeekend())
        {
            player->CastSpell(player, 6668, false);
            ChatHandler(player->GetSession()).SendSysMessage("Its the Weekend...Double XP Activated!");
            player->HandleEmote(ANIM_EMOTE_DANCE);
        }
           
    }

    void OnGiveXP(Player* p, uint32& amount, Unit* victim)
    {
        if (IsWeekend())
            amount *= 2;
        else
            amount == amount;
    }
};

void Addmod_xpweekendScripts()
{
    new xp_weekend();
}