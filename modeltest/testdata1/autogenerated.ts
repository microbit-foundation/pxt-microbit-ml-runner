// Auto-generated. Do not edit.
namespace testrunner {
    export namespace event {
        //% fixedInstance block="Not a spell"
    export const NotASpell = new MlEvent(2, "Not a spell");
    //% fixedInstance block="flick-and-wait"
    export const Flickandwait = new MlEvent(3, "flick-and-wait");
    //% fixedInstance block="waggle"
    export const Waggle = new MlEvent(4, "waggle");
    //% fixedInstance block="Poke"
    export const Poke = new MlEvent(5, "Poke");
    //% fixedInstance block="circle"
    export const Circle = new MlEvent(6, "circle");
  
      }
      
    events = [event.Unknown,event.NotASpell,event.Flickandwait,event.Waggle,event.Poke,event.Circle];
      
    control.onEvent(MlRunnerIds.MlRunnerInference, 1, () => {
      if (!event.Unknown.onStartHandler) {
        maybeUpdateEventStats(event.Unknown);
      }
    });
    control.onEvent(MlRunnerIds.MlRunnerInference, 2, () => {
      if (!event.NotASpell.onStartHandler) {
        maybeUpdateEventStats(event.NotASpell);
      }
    });
    control.onEvent(MlRunnerIds.MlRunnerInference, 3, () => {
      if (!event.Flickandwait.onStartHandler) {
        maybeUpdateEventStats(event.Flickandwait);
      }
    });
    control.onEvent(MlRunnerIds.MlRunnerInference, 4, () => {
      if (!event.Waggle.onStartHandler) {
        maybeUpdateEventStats(event.Waggle);
      }
    });
    control.onEvent(MlRunnerIds.MlRunnerInference, 5, () => {
      if (!event.Poke.onStartHandler) {
        maybeUpdateEventStats(event.Poke);
      }
    });
    control.onEvent(MlRunnerIds.MlRunnerInference, 6, () => {
      if (!event.Circle.onStartHandler) {
        maybeUpdateEventStats(event.Circle);
      }
    });
  
    getModelBlob = (): Buffer => {
      const result = hex`4C444F4D600014002A00030000000000000000053333B33E0C4E6F742061207370656C6C00000000A470BD3E0F666C69636B2D616E642D77616974005C8F423F07776167676C6500CDCC4C3F05506F6B65000000CDCC4C3F07636972636C6500620F47304D4C344650000000F80D0000A40500000000000000000000A80000000800000001000000080000000100000000000000000000000000000000000000180000000000000005000000000000002DE9F05F0F460169091839600021796038680346B3EC1E1A07F2080292EC010A20EE010A30EE210AA2EC010A92EC010A20EE020A30EE220AA2EC010A92EC010A20EE030A30EE230AA2EC010A92EC010A20EE040A30EE240AA2EC010A92EC010A20EE050A30EE250AA2EC010A92EC010A20EE060A30EE260AA2EC010A92EC010A20EE070A30EE270AA2EC010A92EC010A20EE080A30EE280AA2EC010A92EC010A20EE090A30EE290AA2EC010A92EC010A20EE0A0A30EE2A0AA2EC010A92EC010A20EE0B0A30EE2B0AA2EC010A92EC010A20EE0C0A30EE2C0AA2EC010A92EC010A20EE0D0A30EE2D0AA2EC010A92EC010A20EE0E0A30EE2E0AA2EC010A92EC010A20EE0F0A30EE2F0AA2EC010A02F22402B3EC121A07F2440292EC010A20EE010A30EE210AA2EC010A92EC010A20EE020A30EE220AA2EC010A92EC010A20EE030A30EE230AA2EC010A92EC010A20EE040A30EE240AA2EC010A92EC010A20EE050A30EE250AA2EC010A92EC010A20EE060A30EE260AA2EC010A92EC010A20EE070A30EE270AA2EC010A92EC010A20EE080A30EE280AA2EC010A92EC010A20EE090A30EE290AA2EC010A02F23C02386800F2C00307F268021024B3EC010A07F20801F1EC0E0AF3EC0E7A60EEA70A21EE081A30EE200A61EEA81A30EE010A22EE092A30EE210A62EEA92A30EE020A23EE0A3A30EE220A63EEAA3A30EE030A24EE0B4A30EE230A64EEAB4A30EE040A25EE0C5A30EE240A65EEAC5A30EE050A26EE0D6A30EE250A66EEAD6A30EE060A27EE0E7A30EE260A30EE070AF1EC0A0AF3EC0A7A60EEA70A21EE081A30EE200A61EEA81A30EE010A22EE092A30EE210A62EEA92A30EE020A23EE0A3A30EE220A63EEAA3A30EE030A24EE0B4A30EE230A64EEAB4A30EE040A25EE0C5A30EE240A30EE050AA2EC010A013C8FD107F2680210680028B8BF40F2000001C210680028B8BF40F2000001C210680028B8BF40F2000001C210680028B8BF40F2000001C210680028B8BF40F2000001C210680028B8BF40F2000001C210680028B8BF40F2000001C210680028B8BF40F2000001C210680028B8BF40F2000001C210680028B8BF40F2000001C210680028B8BF40F2000001C210680028B8BF40F2000001C210680028B8BF40F2000001C210680028B8BF40F2000001C210680028B8BF40F2000001C210680028B8BF40F2000001C2386800F2007307F208020524B3EC010A07F26801F1EC0E0AF3EC0E7A60EEA70A21EE081A30EE200A61EEA81A30EE010A22EE092A30EE210A62EEA92A30EE020A23EE0A3A30EE220A63EEAA3A30EE030A24EE0B4A30EE230A64EEAB4A30EE040A25EE0C5A30EE240A65EEAC5A30EE050A26EE0D6A30EE250A66EEAD6A30EE060A27EE0E7A30EE260A30EE070AF1EC020AF3EC027A60EEA70A21EE081A30EE200A30EE010AA2EC010A013CAFD107F208021046052100F002F8BDE8F09F012938B5D0ED002A29D9031D00EB8102F3EC017AF4EE627AF1EE10FAC8BFF0EE672A9A42F4D1002402EE104A054695ED000A30EE620A00F015F80134A14232EE002AA5EC010AF2D8002390ED007AC7EE027A01339942E0EC017AF6D838BD0029E1D138BDDFED297AB4EEE70AF1EE10FA48D4DFED277AB4EEE70AF1EE10FA3ADCDFED247ADFED244A9FED243ADFED243A9FED245A9FED244ADFED245A9FED246ADFED246A60EE277AB7EE007A77EEA47A77EEE47AA7EE830AFDEEE74AA7EEA30AF0EE457AE4EE007A14EE903AE7EE805AA5EE806AE6EE006AF0EE667AF0EE476AE7EE806AA6EE807A17EE102A02EBC35300EE103A7047DFED107AB7EE007A87EE270A70479FED0C0A704700000000AAC20000AE423BAAB83F0000404B007231BF8EBEBFB56E2F093C00A0B43AADAD2A3D28AA2A3EFBFFFF3E00000000091FFF3F1100F4BFA3E6DB3F26A1E2BF189FAF3F468421BF7E92A040A31571BE86368140B5C0173F9F13B240BA0A82409397F33FEF1001407601C83F49570440E2741F40B9898440014E4B40B931B7BF7B9A684023A203C096E7224098BB9DBFDF28713FFE1893BF6A707F3F87AACDBF8FC87E3F9E31E6BF2F7FA03DC8C2D3BFEB16B13DD8EB02C02672EA3DB43982C09C2B22412083A9BFD7F384410AB4D4BF1A8E7841FA9190BFD744664094C301C0E86D77405E4445C068CF8E4062A28DC0FD89B13D0501413E8408413E6261DD3E65F9D43EE1BB46BE2CC53E3E86B4723E25A65CBD637A57BDEEDCE83DD5C9C53D1D7C5E3E3161DCBD62949E3CB62DB9BCA011B6BD0053923EC85BA63E22BA4D3E3A9A583C0307E93DD056303D6EB88CBC2071013E048DE53D86F8FABE7B44CB3E58E228BE1D3880BDB30A3B3EB3AEBDBE3DFB46BE3251E7BE0279F9BC990AF8BE1DA8303FFEF95BBE1310333E16F5853ED21789BDC8AB9CBE59CB623DE55E193DB331B93DB8B6BBBE118C043E7874E7BE540E9E3EA45850BD5D30043ED0A360BEF8E1973EDABCAEBD0E8F87BBD108EABAD429993C63919B3E3AB6183D486937BEF5C4853EB73C09BE529CBFBC770BD13DDBF7E93E5F4BC8BE7BCDB43EE8C4AA3EF8C1093CE08D763EE495083FAC56C63E42EEE53D7145D0BEE7F84A3DF820D03D4EE5B8BE2DC510BDA1F779BE123AE53E4A1F193E1763D9BE1C0128BBDFB1AE3DA3BC0EBEC9CBC6BD5366CD3D45315ABE46BC0EBD0D86DD3E05249BBEDAB486BEA93A723D6A85183E5053173E016A4FBE77E0B13C46F885BE54A3913D7833843E0C5FCC3D65C32CBF6642A1BE78A1AA3E4C0DE2BD06732D3F494AB7BE26BF34BEA685F93E885652BD6EC79CBE978441BEF66EEF3DDEB8AC3E0DACB7BC36BBCABEFE2ACA3D7B2F5B3E353AED3E7E0599BD2FA003BF0EE13A3D6DC090BB8ABA02BF26FFF63E67A73C3D4B84843DFA23043EF0FB1F3C284F1FBD94D544BEBBCF57BECCF0A83EE3776CBEB0019EBA91BE0A3ED905CDBDD8025ABE5758FD3E6FAAFB3C921E0E3E91D25A3EB77A3F3D541236BE1DA15C3EF35B2EBEDFBF04BE33EE24BE6F32AF3E16C0663D43B009BE93F268BE3AB4423E36769B3D50A1343F3A5D00BF2587C13E4B77A6BEC58A8CBD5E2A3A3D2876D3BD367CE0BE553951BEEFAA8EBEB0991ABFDDEC19BE5AF00BBE674B2E3ED5D3C2BDA100C13C5F86B9BE5DCC75BDD65271BDBE12CB3EC42315BE33E0E83DED52233FD8A1913D14C73C3F8A33003EA1C6E2BD1E49383E1F125FBECBDC8BBDEB9C82BE453E40BEB2707A3D2C54D43EC8B52B3E0E5955BED49131BF0DE62EBE564095BD0383D63DA197B9BE84E3943BFC53D3BE127872BE74395EBDC5A7743E8D73333D5E647ABE0A2CCCBEB08BFBBDA071383EAC436C3E2143593E991590BE431CA13E010DF03D3331F33EBBFCC23E3F848B3EABD00F3E91BBCC3D1A372D3E08AB5CBE6623B2BC0AC593BE8A0FA13D9AD182BE80D9F93E4A3EAB3EAAA3103E80CC52BEF99B393E4350723D188BC4BE8E427FBDC828123E41DC8D3D6F5A1A3E29D0EA3D4443913E84FF36BDDE8ED8BDD8F2D0BEE502AC3E05FF4E3D03A19B3E78E36BBDEAD69E3EA9F5023EE4AAD33E8801203EEB5C4C3F6E13263F745A6F3DB8DB64BEC1F82C3EEFBC283E5AED973ED8BF4EBEC2998D3D0380BEBD6BAAAFBEA61000BD677E993E5F04BEBDF46C44BDDFFB9F3E098AB43E911C633E1CD91DBE3CB6BE3E10708EBEA4D268BE7CCA923C0BFF96BE9A8650BE8A587D3EE91A37BF1AAD88BEEBE279BE50A6F4BD278F763D2F8C1F3ED0B0A93ECAEC03BE73789F3E382C883EBE8163BEC0149BBE8C3029BEA63A97BE484B953C2E67753E62EC87BEA7A7843DC9868FBE54C946BE56F1C33D466B313E37059EBE594D833EE808BBBE8DACA83D0D78453E3AD28EBD877052BDE00A4F3E6D24A33EA63EAFBE824983BEE91724BF1535B9BEC4B417BD188AD53D9A4F5FBE64D58F3ED55CDB3C43A0983E0202523D24FFB03E5C185D3D847D8F3C021CA4BB8C95A5BDF00390BD11A445BD410605BE029CE0BE40EE48BE4A8C8FBEAA28DB3D139595BCD440003E7A826C3EF6B3703EE02AA83E7484AFBE5470C0BED88DD1BE50607DBE9D26A2BD13F4693E286E0FBEBD19D83DF39E76BD2E7206BEF954853E9A8AEFBCE329BBBEB0460DBB563687BE9DF5173DF027C8BDBE7BD0BEBF76003E8FC1E53E68050D3F0DB386BD4ADD22BEDE4491BE00BAE8BE49EA893D78B0CA3ED4D4B93E67F3373ECA04153FE938D43E0B843D3EA98C4C3EE405F63D6E90803E417D083E35D6CFBD084080BD239215BE0A6BF3BE15492DBF95468FBE3F327E3EF3967DBE25D46FBEF70A3B3ED33D60BD1E06463C2A77E13E3FC214BE3A70B33EC3CC0B3E5D61FFBE9519A1BDEE3A20BFFEE4813DD674023E2A16153E0F14A3BD99BB3BBD0309893D1D6F0DBE158418BD95800BBE8039ED3E65FBB0BE6AA8D6BCE456933EFC85883D26C946BE5E67953E14DBC8BE59D3F0BEA1E5E3BE83BCAC3EFF26813FDA24ADBED6B5413FEFF559BF77CE393F853EB03CE79F98BEBC9B693E8E7C143A41CB88BE4E21663F281CA23E904A1FBE80D1BB3E27EF29BF8CB90CBFBAD5E0BE5D7E183E3685F5BD1EFFADBDCC83763F4146A1BE5BB947BE59A9023F5415AB3E565B4CBE18473E3FAC9A2BBE8F568E3ECDB302BEC612733D94E7B0BEE0EC2D3FFAF6DB3B1C94E9BE2446DCBDBB3392BE70B53DBE5150953ECD8D953F396665BC3238F6BD114F8CBED0B027BE27751CBE25967ABE8A0BB8BEB20692BEEA87943FAAB6CC3D08B2FA3E9FFC7DBC349D18BEBABC0F3E2B5426BE52DEB23E606807BF146C74BC16AFB83D229F6EBE8A6D0DBD86BA29BFB9237F3E4BA3B33E64F6EDBE9568F73C0FDE38BEC70593BE3B7E64BFBB497D3E6A855FBF0AC51F3DCB56EF3D9AAE873952C4773F9236B6BE80CF3A3FE7808F3D7DB27B3FFE935EBF0000000000000000`;
      return result;
    };
  
    simulatorSendData();
  }
  
  // Auto-generated. Do not edit. Really.
  