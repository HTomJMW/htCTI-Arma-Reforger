[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Activation Area")]
class SCR_CTI_ActivationAreaClass : ScriptedGameTriggerEntityClass
{
};

//! Callback delegate used by events regarding character(s) in SCR_CTI_ActivationArea.
void CTI_ActivationAreaCharacterEventDelegate(SCR_CTI_ActivationArea area, Faction affiliatedFaction, IEntity character);
typedef func CTI_ActivationAreaCharacterEventDelegate;
typedef ScriptInvokerBase<CTI_ActivationAreaCharacterEventDelegate> CTI_ActivationAreaEvent;

/*!
	Activation area is a trigger entity that provides callback and API in regards
	to characters entering and/or leaving the area. Characters must be assigned
	to a faction to be recognized by this area. In addition, the area itself
	must have periodic update enabled, otherwise callbacks might not be raised.
*/
class SCR_CTI_ActivationArea : ScriptedGameTriggerEntity
{
	protected SCR_CTI_Town m_town;
	protected SCR_CTI_GameMode m_gameMode;
	protected SCR_CTI_CreateTeamComponent m_createTeamComponent;
	protected SCR_CTI_CreateMinesComponent m_createMinesComponent;
	protected RplComponent m_pRplComponent;
	
	//! Map of all occupants of this area. key: Faction, value: Array of characters (must be alive)
	protected ref map<Faction, ref array<SCR_ChimeraCharacter>> m_mOccupants = new map<Faction, ref array<SCR_ChimeraCharacter>>();

	//! Callback raised when a character enters this area
	protected ref CTI_ActivationAreaEvent m_pOnCharacterEnter = new CTI_ActivationAreaEvent();

	//------------------------------------------------------------------------------------------------
	//! Returns invoker that is invoked when a character enters this area.
	CTI_ActivationAreaEvent GetCharacterEnterInvoker()
	{
		return m_pOnCharacterEnter;
	}

	//! Callback raised when a character leaves this area
	protected ref CTI_ActivationAreaEvent m_pOnCharacterExit = new CTI_ActivationAreaEvent();

	//------------------------------------------------------------------------------------------------
	//! Returns invoker that is invoked when a character exits this area.
	CTI_ActivationAreaEvent GetCharacterExitInvoker()
	{
		return m_pOnCharacterExit;
	}

	//------------------------------------------------------------------------------------------------
	//! Initializes this area by initializing and preallocating required resources.
	protected override void OnInit(IEntity owner)
	{
		// Do not spam messages outside of playmode,
		// these might not be relevant (yet) also
		// there is no need to initialize the entity (just yet)
		if (!GetGame().InPlayMode())
			return;

		// Mandatory, cannot work without factions
		FactionManager factionManager = GetGame().GetFactionManager();
		if (!factionManager)
		{
			Debug.Error("No faction manager present in the world! ActivationArea will malfunction!");
			return;
		}

		// Neccessary to determine replication logic
		m_pRplComponent = RplComponent.Cast(FindComponent(RplComponent));
		if (!m_pRplComponent)
		{
			Debug.Error("SCR_CTI_ActivationArea requires RplComponent to function!");
			return;
		}
		
		m_gameMode = SCR_CTI_GameMode.GetInstance();
		m_town = SCR_CTI_Town.Cast(GetParent());

		// Enable OnFrame event mask
		SetEventMask(EntityEvent.FRAME);

		array<Faction> availableFactions = {};
		factionManager.GetFactionsList(availableFactions);

		// Fetch available actions and preallocate map arrays
		foreach (Faction faction : availableFactions)
			m_mOccupants.Insert(faction, new array<SCR_ChimeraCharacter>());
		
		// Find components
		m_createTeamComponent = SCR_CTI_CreateTeamComponent.Cast(FindComponent(SCR_CTI_CreateTeamComponent));
		if (!m_createTeamComponent)
		{
			Debug.Error("SCR_CTI_ActivationArea requires SCR_CTI_CreateTeamComponent to function!");
			return;
		}

		m_createMinesComponent = SCR_CTI_CreateMinesComponent.Cast(FindComponent(SCR_CTI_CreateMinesComponent));
		if (!m_createMinesComponent)
		{
			Debug.Error("SCR_CTI_ActivationArea's SCR_CTI_CreateMinesComponent missing.");
			return;
		}
	}

	//------------------------------------------------------------------------------------------------
	/*!
		Called when Item is initialized from replication stream. Carries the data from Master.
	*/
	protected override bool RplLoad(ScriptBitReader reader)
	{
		return true;
	}

	//------------------------------------------------------------------------------------------------
	/*!
		Called when Item is getting replicated from Master to Slave connection. The data will be
		delivered to Slave using RplInit method.
	*/
	protected override bool RplSave(ScriptBitWriter writer)
	{
		return true;
	}

	//------------------------------------------------------------------------------------------------
	//! By default queries only for characters of SCR_ChimeraCharacter type
	protected override bool ScriptedEntityFilterForQuery(IEntity ent)
	{
		// Filter for characters only
		SCR_ChimeraCharacter character = SCR_ChimeraCharacter.Cast(ent);
		if (!character)
			return false;

		// That are alive.
		return !character.GetCharacterController().IsDead();
	}

	//------------------------------------------------------------------------------------------------
	//! callback - activation - occurs when and entity which fulfills the filter definitions enters the Trigger
	protected override void OnActivate(IEntity ent)
	{
		SCR_ChimeraCharacter character = SCR_ChimeraCharacter.Cast(ent);
		Faction faction = character.GetFaction();

		if (faction && !m_mOccupants[faction].Contains(character)) // BIS bug: not unique
		{
			m_mOccupants[faction].Insert(character);
			OnCharacterEntered(faction, character);
		}
		
		if (m_pRplComponent.IsProxy()) return;
		
		if (!m_town.isActive() && m_town.getFactionKey() != faction.GetFactionKey())
		{
			m_town.setActiveTime(m_gameMode.GetElapsedTime());
			m_town.setActive(true);
			m_createTeamComponent.OnTriggerActivate();
			m_createMinesComponent.OnTriggerActivate();
			PrintFormat("CTI :: Town %1 is Active", m_town.getTownName());
		}
	}

	//------------------------------------------------------------------------------------------------
	//! Occurs when a [character] of provided [faction] enters the area.
	protected event void OnCharacterEntered(Faction faction, SCR_ChimeraCharacter character)
	{
		m_pOnCharacterEnter.Invoke(this, faction, character);
		
		if (m_pRplComponent.IsProxy()) return;

		// TODO enemy report notif
	}

	//------------------------------------------------------------------------------------------------
	//! callback - deactivation - occurs when and entity which was activated (OnActivate) leaves the Trigger
	protected override void OnDeactivate(IEntity ent)
	{
		SCR_ChimeraCharacter character = SCR_ChimeraCharacter.Cast(ent);
		Faction faction = character.GetFaction();

		if (faction)
		{
			m_mOccupants[faction].RemoveItem(character);
			OnCharacterExit(faction, character);
		}
	}

	//------------------------------------------------------------------------------------------------
	//! Occurs when a [character] of provided [faction] leaves the area.
	protected event void OnCharacterExit(Faction faction, SCR_ChimeraCharacter character)
	{
		m_pOnCharacterExit.Invoke(this, faction, character);
		
		if (m_pRplComponent.IsProxy()) return;
		
		if (m_town.getFactionKey() != faction.GetFactionKey()) m_town.setActiveTime(m_gameMode.GetElapsedTime());
	}

	//------------------------------------------------------------------------------------------------
	/*!
		Fills the provided [outCharacters] array with all occupants of provided [faction].
		\param faction Faction to filter for
		\param outCharacters Output array
		\return Number of items output
	*/
	int GetOccupants(Faction faction, notnull array<SCR_ChimeraCharacter> outCharacters)
	{
		array<SCR_ChimeraCharacter> characters = m_mOccupants[faction];
		if (!characters || characters.IsEmpty())
			return 0;

		outCharacters.Copy(characters);
		return characters.Count();
	}

	//------------------------------------------------------------------------------------------------
	/*!
		Returns the number of occupants of provided [faction].
		\param Faction The faction to return the count for
		\return Returns number of occupants
	*/
	int GetOccupantsCount(Faction faction)
	{
		return m_mOccupants[faction].Count();
	}

	//------------------------------------------------------------------------------------------------
	/*!
		Updates the internal state of the area and reevaluates the owner.
	*/
	protected override event void OnFrame(IEntity owner, float timeSlice)
	{
		super.OnFrame(owner, timeSlice);

		// Since trigger can be out of sync with character states,
		// filter out dead characters if any are left in the collection
		foreach (Faction faction, array<SCR_ChimeraCharacter> characters : m_mOccupants)
		{
			for (int i = characters.Count() - 1; i >= 0; --i)
			{
				SCR_ChimeraCharacter occupant = characters[i];
				if (!occupant || occupant.GetCharacterController().IsDead())
				{
					characters.Remove(i);
					continue;
				}
			}
		}
	}
};
